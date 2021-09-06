/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:28:41 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/06 13:32:48 by zqadiri          ###   ########.fr       */
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

void	error_exit(char *arg, int id)
{
	if (id == 1)
	{
		ft_putendl_fd("exit", 1);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit (255);
	}
	else if (id == 0)
	{
		ft_putendl_fd("exit", 1);
		exit (atoi_exit(arg));
	}
}

long long	atoi_exit(const char *str)
{
	int					signe;
	unsigned long long	r;
	char				*error_tmp;

	error_tmp = (char *)str;
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
		if (r > LLONG_MAX)
		{
			ft_putendl_fd("exit", 1);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(error_tmp, 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit (255);
		}
		str++;
	}
	r = r * signe;
	ft_putendl_fd("exit", 1);
	exit (r);
}

void	exit_number(char *arg)
{
	int	i;
	int in;

	i = 0;
	in = 0;
	if (arg[i] != '\0')
	{
		while (arg[i])
		{
			if (arg[0] == '-' || arg[0] == '+')
				i++;
			if (arg[i] < 48 || arg[i] > 57 )
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
	atoi_exit(arg);
}

int	exit_builtin(char **args)
{
	if (len(args) > 2)
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
