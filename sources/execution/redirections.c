/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 16:28:20 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/07 14:34:35 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** redirect stdin to read from the pipe
** redirect stdout to outfile_fd 
*/

void	setup_infiles(t_cmd *cmd, t_data *m)
{
	int	i;
	int	fd;

	i = -1;
	while (++i < cmd->redir_nbr)
	{
		if (cmd->r[i].type == less)
		{
			fd = open(cmd->r[i].filename, O_RDWR);
			m->redir->infile = fd;
			if (fd < 0)
			{
				m->redir->err = 1;
				print_error(cmd->r[i].filename);
			}
		}
	}
	if (!m->redir->err)
		dup2(m->redir->infile, 0);
}

void	setup_outfiles(t_cmd *cmd, t_data *m)
{
	int	i;
	int	j;
	int	fd;

	i = -1;
	j = 0;
	while (++i < cmd->redir_nbr)
	{
		if (cmd->r[i].type == great)
		{
			fd = open(cmd->r[i].filename, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
			m->redir->outfile = fd;
			check_valid_fd(m, cmd->r[i].filename, fd);
			j++;
		}
		else if (cmd->r[i].type == greater)
		{
			fd = open(cmd->r[i].filename, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
			m->redir->outfile = fd;
			check_valid_fd(m, cmd->r[i].filename, fd);
			j++;
		}
	}
	if (!m->redir->err)
		dup2(m->redir->outfile, 1);
}

		printf ("here\n");
int	setup_redirections(t_cmd *cmd, t_data *m)
{
	int	i;

	i = 0;
	if (count(cmd, less) != 0)
	{
		setup_infiles(cmd, m);
	}
	if (((count(cmd, great) != 0) || (count(cmd, greater)) != 0) && \
		!m->redir->err)
	{
		setup_outfiles(cmd, m);
	}
	return (1);
}

/*
**	exec_single_cmd() executes single commands , 
**	commands with redirections and no pipes
*/

void	exec_single_cmd(t_cmd *cmd, t_data *m)
{
	char	*possible_path;
	pid_t	child_pid;
	int		status;
	int		fd;

	setup_redirections(cmd, m);
	if (is_builtin(cmd) && !m->redir->err)
	{
		check_builtin(cmd);
		restore_std(m->saved_stdout, m->saved_stdin);
		return ;
	}
	else if (!is_builtin(cmd) && !m->redir->err)
	{
		child_pid = fork();
		if (child_pid < 0)
		{
			write (2, "Fork failed !\n", 14);
			exit (1);
		}
		if (child_pid == 0)
		{
			if (!ft_strcmp(cmd->argvs[0], "\0"))
				exit(0);
			possible_path = find_path (cmd->argvs[0], m->path);
			// printf("%s\n", possible_path);
			if (possible_path == NULL)
				possible_path = ft_strdup(cmd->argvs[0]);
			fd = open(possible_path, O_RDONLY);
			if (fd < 0)
			{
				write (2, "minishell: ", 11);
				write(2, possible_path, ft_strlen(possible_path));
				ft_putendl_fd(": command not found", 2);
				exit (127);
			}
			if (execve (possible_path, cmd->argvs, g_global->env_var))
				exit (126);
		}
		else
			waitpid(child_pid, &status, 0);
	}
}
