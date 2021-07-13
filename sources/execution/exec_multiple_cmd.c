/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 09:18:12 by zqadiri           #+#    #+#             */
/*   Updated: 2021/07/13 19:17:27 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_m(t_data *m)
{
	m->redir = malloc(sizeof(t_redir));	
	m->saved_stdout = dup(1);
	m->saved_stdin = dup(0);
	m->path = get_path();
	m->pid = 0;
	m->pipe_fd = malloc(sizeof(int) * 2);
	m->in = 0;
}

int		check_if_builtin(t_cmd	*cmd, t_data *m, int in, int out)
{
	(void)cmd;
	(void)m;
	(void)in;
	(void)out;
	return (1);
}



int	exec_proc(int in, int out, t_cmd *cmd, t_data *m)
{
	int i;
	char *possible_path;

	i = 0;
	// ! check builtin
	check_if_builtin(cmd, m, in, out);
	if ((m->pid = fork()) == 0)
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
	return m->pid;
}

int	setup_in(t_cmd *cmd, t_data *m, int is_first)
{
	int	count;
	int fd;

	(void)m;
	count = check_each_type(cmd, less);
	if (count == 0 && is_first)
		return(0);
	if (count == 0 && !is_first)
		return (-2);
	count = 0;
	while (count < cmd->redir_nbr)
	{
		if (cmd->r[count].type == less)
		{
			//* add close 
			fd = open(cmd->r[count].filename, O_RDWR);
			if (fd < 0)
			{
				print_error(cmd->r[count].filename);
				return (-1);
			}
		}
		count++;
	}
	return (fd);
}

int	fork_pipes(t_cmd *cmd, t_data *m)
{
	int		i;
	char	*possible_path;
	int		in;
	int		is_first;

	i = 0;
	// ! setup all the redirections
	is_first = 1;
	while (i < cmd->nbr_cmd - 1)
	{
		// * if infile exists in = infile_fd else in = 0 if fd < 0 skip  to the cmd in = -1
		in = setup_in(&cmd[i], &m[i], is_first);
			printf ("%d\n", in);
		if (in == -2)
			
		is_first = 0;
		if (pipe(m[i].pipe_fd))
			return (0);
		exec_proc(in, m[i].pipe_fd[1], &cmd[i], &m[i]);
		close(m[i].pipe_fd[1]);
		in = m[i].pipe_fd[0];
		i++;
	}
	if (in != 0)
		dup2(in, 0);
	possible_path = find_path (cmd[i].argvs[0], m->path);
	if (possible_path == NULL)
		possible_path = ft_strdup(cmd[i].argvs[0]);
	int fd = open(possible_path, O_RDONLY);
	if (fd < 0)
	{
		write (2, "minishell: ", 11);
		write(2, possible_path, ft_strlen(possible_path));
		ft_putendl_fd(": command not found", 2);
		exit (0);
	}
	if (execve (possible_path, cmd[i].argvs, g_global->env_var))
		exit(1);
	return (1);
}

void	exec_multiple_cmd(t_cmd *cmd, t_data *m)
{
	int i;

	i = 0;
	while (i < cmd->nbr_cmd)
	{
		init_m(&m[i]);
		i++;
	}
	fork_pipes(cmd, m);
}