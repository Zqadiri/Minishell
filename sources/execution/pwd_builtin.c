/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:13:16 by zqadiri           #+#    #+#             */
/*   Updated: 2021/07/06 10:00:50 by iidzim           ###   ########.fr       */
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
	else if (ft_strequ(args[0], "cd"))
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

// void	execution(t_cmd *cmd)
// {
// 	int i;

// 	printf("\n***args size = [%d]\n", cmd->args_size);
// 	i = -1;
// 	// while (cmd->argvs[++i])
// 	while (++i < cmd->args_size)
// 		printf ("arg[%d] : |%s|\n", i, cmd->argvs[i]);
// 	printf("i = %d\n", i);
// 	i = -1;
// 	printf("***redirection size = [%d]\n", cmd->redir_nbr);
// 	while (++i < cmd->redir_nbr)
// 		printf ("filename [%s] : type [%u]\n", cmd->r[i].filename, cmd->r[i].type);
// }


// void execution(t_cmd *cmd)
// {
// 	int	i, j;

// 	printf("\n*****************\n");
// 	i = 0;
// 	while (cmd->type != eof)
// 	{
// 		j = -1;
// 		while (++j < cmd[i].args_size)
// 			printf("arg[%d] = [%s]\n", j, cmd[i].argvs[j]);
// 		j = -1;
// 		while (++j < cmd->redir_nbr)
// 			printf("file[%s] = type[%u]\n", cmd[i].r[j].filename, cmd[i].r[j].type);
// 		i++;
// 	}
// 	printf("*****************\n");
// }