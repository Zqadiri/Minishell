/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 09:18:12 by zqadiri           #+#    #+#             */
/*   Updated: 2021/07/12 11:43:12 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    execute(t_cmd *cmd)
{
	//* execute each cmd
	(void)cmd;
}

void    fork_cmd(t_cmd *cmd, t_data *m)
{
	int i;

	i = 0;
	while (i < cmd->nbr_cmd)
	{
		if (cmd[i].redir_nbr != 0)
			setup_redirections(&cmd[i], m);
		if (!is_builtin(&cmd[i]))
		{
			m->pid[i] = fork();
			if (m->pid[i] < 0)
				exit (0);
			else if (m->pid[i] == 0)
				execute(&cmd[i]);
		}
		i++;
	}
}

void    exec_multiple_cmd(t_cmd *cmd, t_data *m)
{
	int i;
	int ret;

	i = 0;
	m->pipe_fds = malloc(sizeof(int) * ((cmd->nbr_cmd - 1) * 2 ));
	m->pid = malloc(sizeof(pid_t) * cmd->nbr_cmd);
	while (i < cmd->nbr_cmd - 1)
	{
		ret = pipe(m->pipe_fds + i * 2);
		if(ret < 0)
			exit (0);  
		i++;
	}
	fork_cmd(cmd, m);
	
}