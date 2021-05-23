/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 10:52:50 by zqadiri           #+#    #+#             */
/*   Updated: 2021/05/23 15:14:08 by zqadiri          ###   ########.fr       */
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
	int i;
	int alpha;

	i = 0;
	if (!arg || arg[0] == '=')
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

void	set_new_env(char **args, int index)
{
	int n;
	char *env;

	n = env_count() + 1;
	g_env_var = realloc_new_env(n);
	env = ft_substr(args[index], 0, ft_strlen(args[index]));
	g_env_var[env_count()] = env;
	
}

void	modify_env(char **args, int index)
{
	int i;

	i = find_env(args[index]);
}

void	set_or_modify(char **args, int i)
{
	int	k;

	k = find_env(args[i]);
	if (k == -1)
		set_new_env(args, i);
	else
		modify_env(args, i);
}

int     export_builtin(char **args)
{
	int i;

	i = 0;
    if (!args[1])
    {
        sort_and_print();
        return (1);
    }
	while (args[i])
	{
		if (!is_valid_env_key(args[i]))
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			continue ;
		}
		i++;
		set_or_modify(args, i);
	}
	return (1);
}
