/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_pipes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 15:19:57 by zqadiri           #+#    #+#             */
/*   Updated: 2021/07/17 17:51:25 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_process(int in, int out, t_cmd *cmd, t_data *m)
{
	int i;
	char *possible_path;

	i = 0;
	// ! check builtin
	if (is_builtin(cmd))
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
	else if ((m->pid = fork()) == 0)
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

int	fork_cmd_pipes(t_cmd *cmd, t_data *m)
{
	int		i;
	int		in;

	i = 0;
	in = 0;
	pipe_all(cmd, m);
	while (i < cmd->nbr_cmd - 1)
	{
		exec_process(in, m[i].pipe_fd[1], &cmd[i], &m[i]);
		close(m[i].pipe_fd[1]);
		in = m[i].pipe_fd[0];
		i++;
	}
	exec_process(in, 1, &cmd[i], &m[i]);
	return (1);
}

void    exec_pipe(t_cmd *cmd, t_data *m)
{
	printf ("in pipe\n");
	int		i;
	pid_t	pid;
	int		status;

	i = 0;
	fork_cmd_pipes(cmd, m);
	// printf ("out");
   	while (i < cmd->nbr_cmd)
	{
		pid = waitpid(m[cmd->nbr_cmd - 1].pid, &status, 0);
		i++;
	}
}
