/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 15:27:50 by zqadiri           #+#    #+#             */
/*   Updated: 2021/07/10 10:13:28 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	env_count(void)
{
	int	i;

	i = 0;
	while (g_global->env_var[i])
		i++;
	return (i);
}

 void	print_sorted_env(char **sorted_env)
{
	int		i;
	int		j;
	char	equ_sign;

	i = 0;
	while (sorted_env[i])
	{
		j = 0;
		equ_sign = 1;
		ft_putstr_fd("declare -x ", 1);
		while (sorted_env[i][j])
		{
			ft_putchar_fd(sorted_env[i][j], 1);
			if (sorted_env[i][j] == '=' && equ_sign)
			{
				ft_putchar_fd('"', 1);
				equ_sign = 0;
			}
			j++;
		}
		if (!equ_sign)
			ft_putendl_fd("\"", 1);
		else
			ft_putchar_fd('\n', 1);
		i++;
	}
}

char	**dup_env(void)
{
	char	**dup;
	int 	i;

	i = env_count();
	dup = (char **)malloc(sizeof(char *) * (i + 1));
	if (!dup)
		return (NULL);
	dup[i] = 0;
	i--;
	while (i != -1)
	{
		dup[i] = ft_strdup(g_global->env_var[i]);
		i--;
	}
	return (dup);
}

void	modify_env(char *arg, char *key)
{
	int i;
	char	*new_value;
	char	*tmp;

	i = find_env(key);
	if (i == -1)
		return ;
	else
	{
		new_value = ft_strdup(arg);
		tmp = g_global->env_var[i];
		g_global->env_var[i] = new_value;
		free (tmp);
	}
}
