/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regular_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 13:44:36 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/09 14:23:36 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	find_cmd_path(t_cmd *cmd, t_data *m)
{
	char	*possible_path;
	int		fd;

	possible_path = find_path (cmd->argvs[0], m->path);
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

/*
** execute_regular_cmd() executes regular command, commands with no
** redirections & no pipes
*/

int	execute_regular_cmd(t_cmd *cmd, t_data *m)
{
	pid_t	child_pid;

	if (is_builtin(cmd))
		return (check_builtin(cmd));
	else
	{
		child_pid = fork();
		g_global->pid = child_pid;
		if (child_pid < 0 )
			fork_failed();
		else if (child_pid == 0)
		{
			if (!cmd->argvs)
				exit(0);
			find_cmd_path(cmd, m);
		}
		wait_children();
	}
	return (1);
}
