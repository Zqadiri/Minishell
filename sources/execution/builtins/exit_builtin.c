/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:28:41 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/05 12:25:36 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_exit(void)
{
	exit(EXIT_SUCCESS);
}

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
** non numeric arg
** more then one arg
*/

// unsigned ll

long long	ft_atoi_exit(char *str)
{
	int			i;
	int			j;
	long		neg;
	long long	result;

	neg = 1;
	i = 0;
	j = 0;
	result = 0;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			neg *= -1;
	while (str[i] && (ft_isspace(str[i]) || str[i] == '0'))
		i++;
	while (str[i] >= '0' && str[i] <= '9' && ++j)
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result * neg);
}

void	exit_error(char *arg, char **args)
{
	(void)args;
	ft_putstr_fd("exit", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	ft_exit();
}

void	check_arg(char *arg, char **args)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (arg[i] != '\f' && arg[i] != '\t' && arg[i] != '\r'
			&& arg[i] != '\v' && arg[i] != ' ')
		{
			if (arg[i] < 48 || arg[i] > 57)
				exit_error(arg, args);
		}
		i++;
	}
}

int	exit_builtin(char **args)
{
	int			i;
	long long	exit_code;

	i = 0;
	if (!args[1])
		ft_exit();
	check_arg(args[1], args);
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		ft_exit();
	}
	else
		exit_code = ft_atoi_exit(args[1]);
	ft_exit();
	return (1);
}
