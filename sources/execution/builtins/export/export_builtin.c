/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 10:52:50 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/16 15:43:34 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static void	sort_and_print(void)
{
	char	**dup;
	char	*tmp;
	int		i;
	int		j;

	dup = dup_env();
	i = 0;
	while (dup[i])
	{
		j = i + 1;
		while (dup[j])
		{
			if (ft_strcmp(dup[i], dup[j]) > 0)
			{
				tmp = dup[i];
				dup[i] = dup[j];
				dup[j] = tmp;
			}
			j++;
		}
		i++;
	}
	print_sorted_env(dup);
	free (dup);
}

/*
** Variable Names: Lower-case, digits, with underscores to separate words. 
** Ex: my_variable_name
*/

/*
** Constants and Environment Variable Names: All caps,
** separated with underscores, 
** declared at the top of the file. Ex: MY_CONSTANT
*/

int	is_valid_env_key(char *arg)
{
	int	i;
	int	alpha;

	i = 0;
	alpha = 0;
	if (arg == NULL || arg[0] == '=')
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (ft_isalpha(arg[i]))
			alpha = 1;
		else
		{
			if (ft_isdigit(arg[i]) && !alpha)
				return (0);
			else if (!ft_isdigit(arg[i]) && arg[i] != '_')
				return (0);
		}
		i++;
	}
	return (1);
}

static void	set_new_env(char *arg)
{
	int		index;
	char	*env;
	int		i;
	// char	*pfree;

	index = 0;
	i = -1;
	if (arg == NULL)
		return ;
	while (arg[++i])
		if (arg[i] == '=')
			index = 1;
	index = (env_count() + 1);
	g_global->env_var = realloc_new_env(index);
	env = ft_substr(arg, 0, ft_strlen(arg));
	g_global->env_var[env_count() - 1] = env;
	g_global->env_var[index] = 0;
	// free (env);
}

static void	set_or_modify(char *arg)
{
	int		is_set;
	int		i;
	char	*key;

	if (arg == NULL)
		return ;
	i = get_str_by_char(arg, '=');
	if (i == -1)
		i = ft_strlen(arg);
	key = ft_substr(arg, 0, i);
	is_set = find_env(key);
	if (is_set == -1)
		set_new_env(arg);
	else
		modify_env(arg, key);
	free (key);
}

int	export_builtin(char **args)
{
	int	i;

	i = 0;
	if (!args[1])
	{
		sort_and_print();
		return (1);
	}
	while (args[i++])
	{
		if (!is_valid_env_key(args[i]) && args[i] != NULL)
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			continue ;
		}
		set_or_modify(args[i]);
	}
	return (1);
}
