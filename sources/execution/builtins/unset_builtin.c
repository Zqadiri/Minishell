/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:20:06 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/21 10:48:42 by zqadiri          ###   ########.fr       */
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

int	check_only_key(char *key)
{
	int		i;

	i = -1;
	if (!key)
		return (-1);
	while (g_global->env_var[++i])
	{
		if (!ft_strcmp(g_global->env_var[i], key))
			return (i);
	}
	return (-1);
}

int	find_env(char *key, char **env_pointer)
{
	int		index;
	char	*sub_env;
	int		i;

	i = -1;
	if (!key)
		return (-1);
	while (env_pointer[++i])
	{
		index = get_str_by_char(env_pointer[i], '=');
		if (index == -1)
			index = ft_strlen(env_pointer[i]);
		else
		{
			sub_env = ft_substr(env_pointer[i], 0, index);
			if (sub_env != NULL && ft_strequ(key, sub_env))
			{
				free(sub_env);
				return (i);
			}
			free (sub_env);
		}
	}
	return (check_only_key(key));
}

char	**realloc_new_env(int env_num, char *arg, char **env_pointer)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = (char **)malloc(sizeof(char *) * (env_num + 2));
	if (!new_env)
		return (NULL);
	while (env_pointer[i])
	{
		new_env[i] = ft_strdup(env_pointer[i]);
		i++;
	}
	new_env[i] = ft_strdup(arg);
	new_env[env_num + 1] = 0;
	free_old_env();
	return (new_env);
}

char	**remove_env_by_key(int index, char **env_pointer)
{
	char			*next_env;
	char			*pfree;
	register int	i;

	i = index;
	while (env_pointer[i + 1])
	{
		next_env = ft_strdup(env_pointer[i + 1]);
		pfree = env_pointer[i];
		env_pointer[i] = next_env;
		free (pfree);
		i++;
	}
	pfree = env_pointer[i];
	env_pointer[i] = 0;
	free (pfree);
	return (env_pointer);
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
	int	env_index_;

	i = -1;
	g_global->exit_status = 0;
	if (!args[1])
		return (1);
	while (args[++i])
	{
		env_index = find_env(args[i], g_global->env_var);
		env_index_ = find_env(args[i], g_global->env_);
		if (env_index_ != -1)
			g_global->env_ = remove_env_by_key(env_index_, g_global->env_);
		if (env_index != -1)
			g_global->env_var = remove_env_by_key(env_index, g_global->env_var);
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
