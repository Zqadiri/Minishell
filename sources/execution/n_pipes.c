/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_pipes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 15:19:57 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/13 16:10:58 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_cmd_path(int in, t_cmd *cmd, t_data *m)
{
	int		fd;
	char	*possible_path;

	if (!cmd->argvs)
		exit(0);
	possible_path = find_path(cmd->argvs[0], m->path);
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
	if (in == 0)
		close (m->pipe_fd[in][0]);
	if (execve (possible_path, cmd->argvs, g_global->env_var))
		exit(126);
}

int	exec_process(int in, int out, t_cmd *cmd, t_data *m)
{
	if (is_builtin(cmd))
		return (exec_builtin(in, out, cmd, m));
	m->pid = fork();
	if (m->pid < 0)
		fork_failed();
	if (m->pid == 0)
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
		exec_cmd_path(in, cmd, m);
	}
	return (m->pid);
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
		if (in != 0)
			close(in);
		in = m->pipe_fd[i][0];
		i++;
	}
	g_global->pid = exec_process(in, 1, &cmd[i], &m[i]);
	return (1);
}

/*
**	exec_simple_pipe() execute commands with pipes only
*/

void	exec_simple_pipe(t_cmd *cmd, t_data *m)
{
	int		i;
	int		status;
	int		signal;

	i = -1;
	while (++i < cmd->nbr_cmd)
		init_m(&m[i]);
	fork_cmd_pipes(cmd, m);
	close_all_pipes(m->pipe_fd, cmd->nbr_cmd - 1);
	g_global->pid = 0;
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			g_global->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			signal = WTERMSIG(status);
			g_global->exit_status = signal + 128;
		}
	}
}
