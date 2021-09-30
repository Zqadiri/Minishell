/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 15:56:12 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/21 10:46:52 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
** env [without any options]
** is used to print environment variables
*/

static void	new_env(char *arg, char *key)
{
	int		i;
	char	*new_value;
	char	*tmp;

	i = find_env(key, g_global->env_);
	if (i == -1)
	{
		i = 0;
		while (g_global->env_[i])
			i++;
		g_global->env_ = realloc_new_env(i, arg, g_global->env_);
	}
	else
	{
		i = find_env(key, g_global->env_);
		if (i == -1)
			return ;
		else
		{
			new_value = ft_strdup(arg);
			tmp = g_global->env_[i];
			g_global->env_[i] = new_value;
			free (tmp);
		}
	}
}

void	add_to_env(char *arg)
{
	int		i;
	char	*key;

	if (arg == NULL)
		return ;
	i = get_str_by_char(arg, '=', 0);
	if (i == -1)
		return ;
	key = ft_substr(arg, 0, i);
	new_env(arg, key);
	free (key);
}

int	env_builtin(void)
{
	int	i;

	i = 0;
	while (g_global->env_[i] != NULL)
	{
		ft_putendl_fd(g_global->env_[i], 1);
		i++;
	}
	return (1);
}
