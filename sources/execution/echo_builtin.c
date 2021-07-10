/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 11:06:29 by zqadiri           #+#    #+#             */
/*   Updated: 2021/07/10 16:58:25 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_n_option(char **args)
{
	int i;
	int j;
	int	nb_options;

	i = 1;
	nb_options = 0;
	while (args[i])
	{
	 	j = 0;
		nb_options++;
		if (args[i][j] && args[i][j] == '-')
		{
			j++;
			while (args[i][j])
			{
				if (args[i][j] && args[i][j] != 'n')
					return (nb_options);
				else
					j++;				
			}
		}
		else
			return (nb_options);
		i++;
	}
	return (nb_options);
}	

int		echo_builtin(char **args)
{
	register int	i;
	int				is_n;

	i = 1;
	is_n = 0;
	if (!args[1])
	{
		ft_putchar_fd('\n', 1);
		return(1);
	}
	if (args[i][0] == '-')
	{
		is_n = check_n_option(args);
		i = is_n;		
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		i++;
		if (args[i])
			ft_putchar_fd(' ', 1);
	}
	if (is_n == 0)
		ft_putchar_fd('\n', 1);
	return (1);	
}
