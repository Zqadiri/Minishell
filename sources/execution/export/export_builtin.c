/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 10:52:50 by zqadiri           #+#    #+#             */
/*   Updated: 2021/05/24 16:01:24 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"


void    sort_and_print(void)
{
	char	**dup;
	char	*tmp;
	int 	i;
	int 	j;

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
	// int k = 0;
	// while (dup[k])
	// {
	// 	printf ("%s\n", dup[k]);
	// 	k++; 
	// }
	print_sorted_env(dup);
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

int		is_valid_env_key(char *arg)
{
	// printf ("is_valid_name{%s}\n", arg);
	int i;
	int alpha;

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

void	set_new_env(char *arg)
{
	int index;
	char *env;
	int i;

	index = 0;
	i = -1;
	if (arg == NULL)
		return ;
	while (arg[++i])
		if (arg[i] == '=')
			index = 1;
	if (index == 0)
		return ;
	else
	{
		index = (env_count() + 1);
		g_env_var = realloc_new_env(index);
		env = ft_substr(arg, 0, ft_strlen(arg));
		g_env_var[env_count() - 1] = env;
		g_env_var[index] = 0;
		// printf ("in set new [%s]\n", g_env_var[env_count()]);
		// env_builtin();
	}
}

void	set_or_modify(char *arg)
{
	// printf ("%s\n", arg);
	int	is_set;
	int		i;
	char	*key;

	// get the key
	if (arg == NULL)
		return ;
	i = get_str_by_char(arg, '=');
	// printf ("iiiii[%d]\n", i);
	if (i == -1)
		i = ft_strlen(arg);
	key = ft_substr(arg, 0, i);
	// printf ("[%d]\n", i);
	// printf("---> key[%s]\n", key);
	is_set = find_env(key);
	if (is_set == -1)
		set_new_env(arg);
	else
		modify_env(arg, key);
}

int     export_builtin(char **args)
{
	int i;

	i = -1;
	if (!args[1])
	{
		sort_and_print();
		return (1);
	}
	while (args[i++])
	{
		// printf ("export builtin %s\n", args[i]);
		if (!is_valid_env_key(args[i]) && args[i] != NULL)
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			continue ;
		}
		set_or_modify(args[i]);
	}
	return (1);
}

// int		main(int argc, char **argv, char **envv)
// {
// 	(void)argc;
// 	argv++;
// 	dup_env_var(envv);
// 	export_builtin(argv);
// 	env_builtin(g_env_var);
// 	return (1);
// }
