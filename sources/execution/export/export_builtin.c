/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 10:52:50 by zqadiri           #+#    #+#             */
/*   Updated: 2021/05/22 13:32:22 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	env_count(void)
{
	int	i;

	i = 0;
	while (g_env_var[i])
		i++;
	return (i);
}

void    print_sorted_env(char **sorted_env)
{
    int i;
    int j;
    int equ_sign;

    i = 0;
    equ_sign = 1;
    while(sorted_env[i])
    {
        j = 0;
        equ_sign = 1;
		ft_putstr_fd("declare -x ", 1);
        while(sorted_env[i][j])
        {
			ft_putchar_fd(sorted_env[i][j], 1);
            if (sorted_env[i][i] == '=' && equ_sign)
            {
				ft_putchar_fd('"', 1);
                equ_sign = 0;
            }
            j++;
        } 
		if (!equ_sign)
			ft_putchar_fd('"', 1);
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
		dup[i] = ft_strdup(g_env_var[i]);
		i--;
	}
	return (dup);
}

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

int     export_builtin(char **args)
{
    if (!args[1])
    {
        sort_and_print();
        return (1);
    }
	return (1);
}