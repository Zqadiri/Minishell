/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 10:52:50 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/24 11:23:17 by zqadiri          ###   ########.fr       */
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
	int		i;

	index = 0;
	i = -1;
	if (arg == NULL)
		return ;
	while (arg[++i])
		if (arg[i] == '=')
			index = 1;
	index = (env_count());
	g_global->env_var = realloc_new_env(index, arg, g_global->env_var);
}

static void	set_or_modify(char *arg)
{
	int		is_set;
	int		i;
	char	*key;

	if (arg == NULL)
		return ;
	i = get_str_by_char(arg, '=', 0);
	if (i == -1)
		i = ft_strlen(arg);
	key = ft_substr(arg, 0, i);
	is_set = find_env(key, g_global->env_var);
	if (is_set == -1)
		set_new_env(arg);
	else
		modify_env(arg, key);
	free (key);
}

static void	new_env(char *arg)
{
	int		index;
	int		i;
	int		is_set;
	char	*key;
	char	*new_value;
	char	*tmp;

	index = 0;
	i = get_str_by_char(arg, '=', 0);
	if (i == -1)
		i = ft_strlen(arg);
	key = ft_substr(arg, 0, i);
	is_set = find_env(key, g_global->env_);
	if (arg == NULL)
		return ;
	if (is_set == -1)
	{
		while (g_global->env_[index])
			index++;
		g_global->env_ = realloc_new_env(index, arg, g_global->env_);
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

static void	add_to_env(char *arg)
{
	int		i;
	char	*key;
	// int		is_set;
	char	*get_key;

	if (arg == NULL)
		return ;
	i = get_str_by_char(arg, '=', 0);
	if (i == -1)
		i = ft_strlen(arg);
	key = ft_substr(arg, 0, i);
	get_key = getenv(key);
	if (get_key == NULL)
	{
		free (key);
		return;
	}
	else
		new_env(arg);
	free (key);
}

int	export_builtin(char **args)
{
	int	i;

	i = 0;
	g_global->exit_status = 0;
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
			g_global->exit_status = 1;
			continue ;
		}
		set_or_modify(args[i]);
		add_to_env(args[i]);
	}
	return (1);
}
