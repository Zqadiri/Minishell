/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 11:06:29 by zqadiri           #+#    #+#             */
/*   Updated: 2021/05/22 10:42:12 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_n_option(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[++i])
	{
		j = 0;
		if (args[i][j++] == '-' && args[i][j] && args[i][j] == 'n')
		{
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] && args[i][j] != 'n')
				return (0);
		}
		else
			return (i);
	}
	return (i);
}

int		echo_builtin(char **args)
{
	register int	i;
	int				is_n;

	i = 0;	
	if (!args[1])
	{
		ft_putchar_fd('\n', 1);
		return(1);
	}
	is_n = check_n_option(args);
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		i++;
		if (args[i])
			ft_putchar_fd(' ', 1);
	}
	if (is_n)
		ft_putchar_fd('\n', 1);
	return (1);	
}
