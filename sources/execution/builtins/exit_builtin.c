/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:28:41 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/05 12:36:01 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_isspace(char c)
{
	if (c == '\f' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == ' ')
		return (1);
	return (0);
}

/*
** errors:
** greater than LONG_MIN   -9223372036854775808
** greater than LONG_MAX
**  non numeric arg
**
*/

void	exit_helper(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[0] == '-' || arg[0] == '+')
			i++;
		if (arg[i] < 48 || arg[i] > 57)
		{
			ft_putendl_fd("exit", 1);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit (255);
		}
		else
		{
			// printf("%d\n", ft_atoi(arg));
			ft_putendl_fd("exit", 1);
			exit(ft_atoi(arg));
		}	
	}	
}

int		exit_builtin(char **args)
{
	if (args[2] != NULL)
	{
		ft_putendl_fd("exit", 1);
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		g_global->exit_status = 1;
		return (0);
	}
	else if (args[1])
	{
		if (!ft_strcmp(args[1], "-9223372036854775808"))
		{
			ft_putendl_fd("exit", 1);
			exit(0);
		}
		exit_helper(args[1]);
	}
	else
	{
		ft_putendl_fd("exit", 1);
		exit (0);
	}
	return (1);
}
