/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_pipes_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 09:18:12 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/01 18:11:41 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_all_pipes(int **fd, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
}

void	init_m(t_data *m)
{
	m->saved_stdout = dup(1);
	m->saved_stdin = dup(0);
	m->path = get_path();
	m->pid = 0;
	m->in = 0;
	m->redir = (t_red *)malloc(sizeof(t_red));
	m->redir->infile = 0;
	m->redir->outfile = 0;
	m->redir->err = 0;
}

int	exec_builtin(int in, int out, t_cmd *cmd, t_data *m)
{
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	if (out != 1)
	{
		dup2(out, 1);
		close(out);
	}
	check_builtin(cmd);
	restore_std(m->saved_stdout, m->saved_stdin);
	return (1);
}

int	exec_proc(int in, int out, t_cmd *cmd, t_data *m, int id)
{
	int		i;
	char	*possible_path;

	i = 0;
	if (is_builtin(cmd))
		return (exec_builtin(in, out, cmd, m));
	if ((m->pid = fork()) == 0)
	{
		if (m->redir->infile && !m->redir->err)
		{
			close(m->pipe_fd[id][0]);
			dup2(m->redir->infile, 0);
		}
		else if (in != 0)
		{
			dup2(in, 0);
			close(in);
		}
		if (m->redir->outfile && !m->redir->err)
			dup2(m->redir->outfile, 1);
		else if (out != 1)
		{
			dup2(out, 1);
			close(out);
		}
		possible_path = find_path(cmd->argvs[0], m->path);
		if (possible_path == NULL)
			possible_path = ft_strdup(cmd->argvs[0]);
		int fd = open(possible_path, O_RDONLY);
		if (fd < 0)
		{
			write (2, "minishell: ", 11);
			write(2, possible_path, ft_strlen(possible_path));
			ft_putendl_fd(": command not found", 2);
			exit (0);
		}
		if (execve (possible_path, cmd->argvs, g_global->env_var))
			exit(1);
	}
	return (m->pid);
}

int	pipe_all(t_cmd *cmd, t_data *m)
{
	int	i;

	i = 0;
	m->pipe_fd = (int **)malloc(sizeof(int *) * cmd->nbr_cmd - 1);
	while (i < cmd->nbr_cmd - 1)
	{
		m->pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
		if (pipe(m->pipe_fd[i]))
			return (0);
		i++;
	}
	return (1);
}

void	setup_in(t_cmd *cmd, t_data *m)
{
	int	cpt;
	int	fd;

	cpt = (count(cmd, less));
	if (cpt == 0)
	{
		m->redir->infile = 0;
		return ;		
	}
	cpt = 0;
	while (cpt < cmd->redir_nbr)
	{
		if (cmd->r[cpt].type == less)
		{
			fd = open(cmd->r[cpt].filename, O_RDWR);
			if (fd < 0)
			{
				print_error(cmd->r[cpt].filename);
				m->redir->err = 1;
				return ;
			}
		}
		cpt++;
	}
	m->redir->infile = fd;
}

void	setup_out(t_cmd *cmd, t_data *m)
{
	int i;
	int fd;

	i = 0;
	while (i < cmd->redir_nbr)
	{
		if (cmd->r[i].type == great)
		{
			fd = open(cmd->r[i].filename, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
			if (fd < 0)
			{
				m->redir->err = 1;
				print_error(cmd->r[i].filename);
			}
		}
		else if (cmd->r[i].type == greater)
		{
			fd = open(cmd->r[i].filename, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
			if (fd < 0)
			{
				m->redir->err = 1;
				print_error(cmd->r[i].filename);
			}
		}
		i++;
	}
	m->redir->outfile = fd;
}

void	setup_all_redirections(t_cmd *cmd, t_data *m)
{
	int i;

	i = -1;
	while (++i < cmd->nbr_cmd)
	{
		if (count(&cmd[i], less) > 0)
			setup_in(&cmd[i], &m[i]);
		if (count(&cmd[i], great) > 0 ||
		count(&cmd[i], great) > 0)
			setup_out(&cmd[i], &m[i]);
	}
}

int	fork_pipes(t_cmd *cmd, t_data *m)
{
	int i;
	int in;
	int		status;

	i = -1;
	in = 0;
	while (++i < cmd->nbr_cmd)
		init_m(&m[i]);
	pipe_all(cmd, m);
	setup_all_redirections(cmd, m);
	i = -1;
	while (++i < cmd->nbr_cmd - 1)
	{
		exec_proc(in, m->pipe_fd[i][1], &cmd[i], &m[i], i);
		close(m->pipe_fd[i][1]);
		in = m->pipe_fd[i][0];
	}
	exec_proc(in, 1, &cmd[i], &m[i], i);
	close_all_pipes(m->pipe_fd, cmd->nbr_cmd - 1);
	while (wait(&status) != -1);
	if (WIFEXITED(status))
			g_global->exit_status = WEXITSTATUS(status);
	return (1);
}

void	exec_multiple_cmd(t_cmd *cmd, t_data *m)
{
	int		i;
	int		is_redir;

	i = 0;
	is_redir = 0;
	while (i < cmd->nbr_cmd)
	{
		if (cmd[i].redir_nbr != 0)
			is_redir = 1;
		i++;
	}
	if (!is_redir)
	{
		printf ("Pipes only !\n");
		exec_simple_pipe(cmd, m);
		return ;		
	}
	else
	{
		printf ("Multiple cmd!\n");
		fork_pipes(cmd, m);
	}
}
