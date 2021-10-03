/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_pipes_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 09:18:12 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/23 12:45:28 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_proc(int write_end, t_cmd *cmd, t_data *m, int *fd)
{
	m->pid = fork();
	if (m->pid == 0)
	{
		if (m->redir->infile && !m->redir->err)
			dup2(m->redir->infile, 0);
		else if (m->read_end != 0)
		{
			dup2(m->read_end, 0);
			close(m->read_end);
		}
		if (m->redir->outfile && !m->redir->err)
			dup2(m->redir->outfile, 1);
		else if (write_end != 1)
		{
			dup2(write_end, 1);
			close(write_end);
		}
		if (cmd->argvs != NULL && is_builtin(cmd))
			check_builtin(cmd);
		else
			exec_cmd_path(cmd, m, fd);
		exit (0);
	}
	return (m->pid);
}

void	setup_all_redirections(t_cmd *cmd, t_data *m)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cmd->nbr_cmd)
	{
		j = -1;
		check_for_heredoc(&m[i], &cmd[i]);
		while (++j < cmd[i].redir_nbr)
		{
			if (cmd[i].r[j].type == less)
				setup_in(&cmd[i], &m[i], j);
			if ((cmd[i].r[j].type == great || cmd[i].r[j].type == greater) && \
				!m->redir->err)
				setup_out(&cmd[i], &m[i], j);
		}
	}
}

int	fork_pipes(t_cmd *cmd, t_data *m)
{
	int		i;

	i = -1;
	m->read_end = 0;
	while (++i < cmd->nbr_cmd)
		init_m(&m[i], i);
	pipe_all(cmd, m);
	setup_all_redirections(cmd, m);
	i = -1;
	while (++i < cmd->nbr_cmd - 1)
	{
		pipe(m->redir->pipe_fd[i]);
		g_global->pid = exec_proc(m->redir->pipe_fd[i][1],
				&cmd[i], &m[i], m->redir->pipe_fd[i]);
		close(m->redir->pipe_fd[i][1]);
		if (m->read_end != 0)
			close(m->read_end);
		m->read_end = m->redir->pipe_fd[i][0];
	}
	g_global->pid = exec_proc(1, &cmd[i], &m[i], NULL);
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
		exec_simple_pipe(cmd, m);
		return ;
	}
	else
	{
		fork_pipes(cmd, m);
		close_all_pipes(m->redir->pipe_fd, cmd->nbr_cmd - 1, m);
		wait_children();
	}
	g_global->pid = 0;
}
