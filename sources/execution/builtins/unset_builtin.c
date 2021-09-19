/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:20:06 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/19 14:37:08 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static	void	free_old_env(void)
{
	int	i;

	i = 0;
	while (g_global->env_var[i])
	{
		free(g_global->env_var[i]);
		g_global->env_var[i] = NULL;
		i++;
	}
	free (g_global->env_var);
	g_global->env_var = NULL;
}

int	find_env(char *key)
{
	int		index;
	char	*sub_env;
	int		i;

	i = -1;
	if (!key)
		return (-1);
	while (g_global->env_var[++i])
	{
		index = get_str_by_char(g_global->env_var[i], '=');
		if (index == -1)
			index = ft_strlen(g_global->env_var[i]);
		else
		{
			sub_env = ft_substr(g_global->env_var[i], 0, index);
			if (sub_env != NULL && ft_strequ(key, sub_env))
			{
				free(sub_env);
				return (i);
			}
			free (sub_env);
		}
	}
	return (-1);
}

char	**realloc_new_env(int env_num, char *arg)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = (char **)malloc(sizeof(char *) * (env_num + 2));
	if (!new_env)
		return (NULL);
	while (g_global->env_var[i])
	{
		new_env[i] = ft_strdup(g_global->env_var[i]);
		i++;
	}
	new_env[i] = ft_strdup(arg);
	new_env[env_num + 1] = 0;
	free_old_env();
	return (new_env);
}

char	**remove_env_by_key(int index)
{
	char			*next_env;
	char			*pfree;
	register int	i;

	i = index;
	while (g_global->env_var[i + 1])
	{
		next_env = ft_strdup(g_global->env_var[i + 1]);
		pfree = g_global->env_var[i];
		g_global->env_var[i] = next_env;
		free (pfree);
		i++;
	}
	pfree = g_global->env_var[i];
	g_global->env_var[i] = 0;
	free (pfree);
	return (g_global->env_var);
}

/*
**  unset a bash environment variable
**  unset arg
**  unset arg1 arg2 *
*/

int	unset_builtin(char **args)
{
	int	i;
	int	env_index;

	i = -1;
	g_global->exit_status = 0;
	if (!args[1])
		return (1);
	while (args[++i])
	{
		env_index = find_env(args[i]);
		if (env_index != -1)
			g_global->env_var = remove_env_by_key(env_index);
		else
		{
			if (!is_valid_env_key(args[i]))
			{
				write (2, "minishell: unset: `", 19);
				write (2, args[i], ft_strlen(args[i]));
				write (2, "': not a valid identifier\n", 26);
				g_global->exit_status = 1;
				continue ;
			}
		}
	}
	return (1);
}
