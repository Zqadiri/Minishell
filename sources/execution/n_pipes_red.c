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
	return (0);
}

int	exec_proc(int in, int out, t_cmd *cmd, t_data *m)
{
	m->pid = fork();
	if (m->pid == 0)
	{
		if (m->redir->infile && !m->redir->err)
			dup2(m->redir->infile, 0);
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
		if (cmd->argvs != NULL && is_builtin(cmd))
			return (exec_builtin(in, out, cmd, m));
		else
			exec_cmd_path(m->id, cmd, m);
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
	m->id = 0;
	while (++i < cmd->nbr_cmd)
		init_m(&m[i], i);
	pipe_all(cmd, m);
	setup_all_redirections(cmd, m);
	i = -1;
	while (++i < cmd->nbr_cmd - 1)
	{
		g_global->pid = exec_proc(m->id, m->redir->pipe_fd[i][1],
				&cmd[i], &m[i]);
		close(m->redir->pipe_fd[i][1]);
		if (m->id != 0)
			close(m->id);
		m->id = m->redir->pipe_fd[i][0];
	}
	g_global->pid = exec_proc(m->id, 1, &cmd[i], &m[i]);
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
