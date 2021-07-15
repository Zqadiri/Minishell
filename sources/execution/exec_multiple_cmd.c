/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 09:18:12 by zqadiri           #+#    #+#             */
/*   Updated: 2021/07/12 16:29:18 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute(t_cmd *cmd, t_data *m)
{
	//* execute each cmd
	exec_single_cmd(cmd, m);
}

void	fork_cmd(t_cmd *cmd, t_data *m)
{
	int i;

	i = 0;
	while (i < cmd->nbr_cmd)
	{
		if (!is_builtin(cmd))
		{
			m->pid = fork();
			if (m->pid < 0)
				exit (0);
			else if (m->pid == 0)
				execute(cmd, m);
		}
		i++;
	}
}

void	init_m(t_data *m)
{
	m->redir = malloc(sizeof(t_redir));	
	m->saved_stdout = dup(1);
	m->saved_stdin = dup(0);
	m->path = get_path();
	m->pid = 0;
}

void	exec_multiple_cmd(t_cmd *cmd, t_data *m)
{
	int i;
	int ret;

	i = 0;
	while (i < cmd->nbr_cmd - 1)
	{
		m[i].pipe_fd = malloc(sizeof(int) * 2);
		ret = pipe(m[i].pipe_fd);
		if(ret < 0)
			exit (0);
		i++;
	}
	i = 0;
	while (i < cmd->nbr_cmd)
	{
		init_m(&m[i]);
		fork_cmd(&cmd[i], &m[i]);		
	}
}
