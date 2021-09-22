/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regular_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 13:44:36 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/22 11:21:44 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	check_if_is_executalble(t_cmd *cmd, int ret)
// {
// 	// if (stat(cmd->argvs[0], &sb) == 0 && sb.st_mode & S_IXUSR)
// 	// if((stat(cmd->argvs[0], &sb) >= 0) && (sb.st_mode > 0) && (S_IEXEC & sb.st_mode))
// 	// if (!stat(cmd->argvs[0], &sb))
// 	// {
// 	// 	if((sb.st_mode > 0) && (S_IEXEC & sb.st_mode))
// 	// 		printf("%s is executable\n", cmd->argvs[0]);
// 	// }
// 	// else  
// 	// 	exit (126);
// 	printf ("here!\n");
// 	struct stat sb;
// 	DIR		*dir;
	
// 	if ((ret == -1) && (ft_strncmp(cmd->argvs[0], "./", 2) && ft_strncmp(cmd->argvs[0] , "../", 3)))
// 	{
// 		write (2, "minishell: ", 11);
// 		write(2, cmd->argvs[0], ft_strlen(cmd->argvs[0]));
// 		ft_putendl_fd(": *permission denied", 2);
// 		exit (126);
// 	}
// 	else
// 	{
// 		if (!(stat(cmd->argvs[0], &sb)) && (S_IEXEC & sb.st_mode))
// 			exit(126);
// 		dir = opendir(cmd->argvs[0]);
// 		if (!dir)
// 		{
// 			write (2, "minishell: ", 11);
// 			write(2, cmd->argvs[0], ft_strlen(cmd->argvs[0]));
// 			ft_putendl_fd(": permission denied", 2);
// 			exit (126);
// 		}
// 		else
// 		{
// 			closedir(dir);
// 			write (2, "minishell: ", 11);
// 			write(2, cmd->argvs[0], ft_strlen(cmd->argvs[0]));
// 			ft_putendl_fd(": is a directory", 2);
// 			exit (126);
// 		}
// 	}
// }

void	check_for_errors(t_cmd *cmd, t_data *m)
{
	if (!cmd->argvs)
		exit(0);
	if (m->redir->err)
	{
		g_global->exit_status = 1;
		exit(g_global->exit_status);
	}
	if (!ft_strcmp(cmd->argvs[0], "\0"))
	{
		write (2, "minishell: ", 11);
		ft_putendl_fd(": command not found", 2);
	}
}

void	find_cmd_path(t_cmd *cmd, t_data *m)
{
	char	*possible_path;
	int		fd;

	check_for_errors(cmd, m);
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
	execve (possible_path, cmd->argvs, g_global->env_var);
	// if (rt == -1)
	// 	check_if_is_executalble(cmd, rt);
}

/*
** execute_regular_cmd() executes regular command, commands with 
** no redirections & no pipes
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
			find_cmd_path(cmd, m);
		wait_children();
		restore_std(m->saved_stdout, m->saved_stdin);
	}
	return (1);
}
