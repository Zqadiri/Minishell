/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 11:06:29 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/19 18:56:31 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_n_option(char **av, int *i, int *option)
{
	int	j;

	*i = 1;
	if (av[1] && av[*i][0] == '-' && av[*i][1] == 'n')
	{
		while (av[*i][0] == '-' && av[*i][1] == 'n')
		{
			j = 1;
			while (av[*i][j] != '\0')
			{
				if (av[*i][j] != 'n')
					return ;
				j++;
			}
			(*i)++;
			*option = 1;
		}
	}
}

int	echo_builtin(char **args)
{
	int		i;
	int		option;

	i = 0;
	option = 0;
	g_global->exit_status = 0;
	if (len(args) == 1)
	{
		ft_putchar_fd('\n', 1);
		return (1);
	}
	else if (!(ft_strcmp(args[1], "-n") && len(args) == 2))
		return (1);
	check_n_option(args, &i, &option);
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (i < len(args) - 1)
			write(1, " ", 1);
		i++;
	}
	if (option == 0)
		write(1, "\n", 1);
	return (0);
}
