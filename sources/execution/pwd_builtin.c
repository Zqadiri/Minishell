/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:13:16 by zqadiri           #+#    #+#             */
/*   Updated: 2021/07/10 13:01:27 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int     pwd_builtin()
{
    char *pwd;

    pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, 1);
	free(pwd);
	ft_putchar_fd('\n', 1);
	return (1);
}

int			check_builtin(t_cmd *cmd)
{
	char **args;

	args = cmd->argvs;
	if ((ft_strequ(args[0], "pwd") || ft_strequ(args[0], "PWD")))
	{
        pwd_builtin();
		return (1);		
	}
	else if (ft_strequ(args[0], "echo"))
		return (echo_builtin(args));
	else if (ft_strequ(args[0], "env"))
		return (env_builtin());
	// else if (ft_strequ(args[0], "cd"))
	// {
	// 	printf ("arg[0]:%s\n", args[0]);
	// 	cd_builtin(args);
	// }
	// else if (ft_strequ(args[0], "unset"))
	// 	return (unset_builtin(args));
	// else if (ft_strequ(args[0], "export"))
	// 	return (export_builtin(args));
	// else if (ft_strequ(args[0], "exit"))
	// 	exit_builtin(args);
	return (0);
}

int		exec_simple_cmd(t_cmd *cmd)
{
	if (!check_builtin(cmd))
		return(0);
	return (1);
}

void	execution(t_cmd *cmd)
{
	g_global = malloc(sizeof(t_global));
	if (cmd->type == eof)
	{
		printf("f:execution\ttype = [%u]\n", cmd->type);
		exec_simple_cmd(cmd);
	}
	else
		printf("f:execution\ttype = [%u]\n", cmd->type);
}
