/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:28:41 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/05 14:52:01 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
** errors:
** greater than LONG_MIN   -9223372036854775808
** greater than LONG_MAX
**  non numeric arg
**
*/

long long	atoi_exit(const char *str)
{
	int					signe;
	unsigned long long	r;

	while (*str >= 9 && *str <= 32)
		str++;
	signe = 1;
	if (*str == '-')
	{
		signe = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	r = 0;
	while (*str >= 48 && *str <= 57)
	{
		r = r * 10 + *str - '0';
		if ((unsigned long long )r > LLONG_MAX)
		{
			ft_putendl_fd("exit", 1);
			exit(255);
		}
		str++;
	}
	r = r * signe;
	return (r);
}

void	exit_number(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '\0')
	{
		while (arg[i])
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
			i++;
		}		
	}
	ft_putendl_fd("exit", 1);
	exit(atoi_exit(arg));	
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
		exit_number(args[1]);
	}
	else
	{
		ft_putendl_fd("exit", 1);
		exit (0);
	}
	return (1);
}
