/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:13:16 by zqadiri           #+#    #+#             */
/*   Updated: 2021/05/21 11:07:27 by zqadiri          ###   ########.fr       */
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

int			check_builtin(char **args)
{
	printf ("in check\n");

	if (ft_strequ(args[0], "echo"))
		return (echo_builtin(args));
	// else if (ft_strequ(args[0], "cd"))
	else if (args[0][0] == 'c' && args[0][1] == 'd')
	{
		printf ("arg[0]:%s\n", args[0]);
		cd_builtin(args);
	}
	else if (ft_strequ(args[0], "unset"))
		return (unset_builtin(args));
	else if (ft_strequ(args[0], "export"))
		return (export_builtin(args));
	else if (ft_strequ(args[0], "exit"))
		exit_builtin(args);
	else if (ft_strequ(args[0], "pwd"))
            pwd_builtin();
	else if (ft_strequ(args[0], "env"))
		return (env_builtin());
	return (0);
}

// int main(void)
// {
//     pwd_builtin();
//     return (0);
// }