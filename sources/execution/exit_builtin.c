/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 17:28:41 by zqadiri           #+#    #+#             */
/*   Updated: 2021/05/18 11:08:21 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** errors:
** greater than LONG_MIN   -9223372036854775808
** greater than LONG_MAX
**  non numeric arg
**
*/

long long   ft_atoi_exit(char *str)
{
    int i;
    int j;
    long neg;
    long long result;

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
        
	}
}

void		exit_error(char *arg, char **args)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	ft_exit(args);
}

void		check_arg(char *arg, char **args)
{
	int		i;

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

void    exit_builtin(char **args)
{
    int         i;
    long long   exit_code;
    
    i = 0;
    if (!args[1]) // with no args
        ft_exit();
    // with args
    check_arg(args[1], args);
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		ft_exit(); // exit function
	}
    else
    {
        exit_code = ft_atoi_exit(args[1])
    }
}