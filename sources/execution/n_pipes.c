/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_pipes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 15:19:57 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/04 13:39:08 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_process(int in, int out, t_cmd *cmd, t_data *m)
{
	int i;
	char *possible_path;

	i = 0;
	printf ("in: %d -> out : %d\n", in , out);
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
		// restore_std(m->saved_stdout, m->saved_stdin);
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
			exit (127);
		}
		if (execve (possible_path, cmd->argvs, g_global->env_var))
			exit(126);
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
		g_global->pid = exec_process(in, m->pipe_fd[i][1], &cmd[i], &m[i]);
		close(m->pipe_fd[i][1]);
		in = m->pipe_fd[i][0];
		i++;
	}
	g_global->pid = exec_process(in, 1, &cmd[i], &m[i]);
	return (1);
}

/*
**	exec_simple_pipe() execute commands with pipes only
*/

void    exec_simple_pipe(t_cmd *cmd, t_data *m)
{
	int		i;
	int		status;
	int		signal;

	i = -1;
	while (++i < cmd->nbr_cmd)
		init_m(&m[i]);
	fork_cmd_pipes(cmd, m);
	close_all_pipes(m->pipe_fd, cmd->nbr_cmd - 1);
	g_global->pid =0;
	waitpid(-1, &status, WCONTINUED);
	if (WIFEXITED(status))
			g_global->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		if (signal == SIGQUIT)
			ft_putstr_fd("quit!", 1);
		g_global->exit_status = signal + 128;
	}
}
