/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:20:06 by zqadiri           #+#    #+#             */
/*   Updated: 2021/05/16 19:39:01 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void free_old_env(char **old_env)
{
    int i;

    i = 0;
    while (old_env[i])
    {
        free(old_env[i]);
        old_env[i] = NULL;
        i++;
    }
    free (old_env);
    old_env = NULL;
}

int get_str_by_char(char *str, char c)
{
	char	*ch;

	ch = ft_strchr(str, c);
	if (!ch)
		return (-1);
	return (ch);
}

int     find_env(char *key)
{
    int index;
    char *sub_env;
    int i;

    i = 0;
    sub_env = NULL;
    if (!key)
        return (-1);
    while (g_env_var[i])
    {
        index = get_str_by_char(g_env_var[i], '=');
        if (index == -1)
            index = ft_strlen(g_env_var[i]);
        else
        {
            sub_env = ft_substr(g_env_var[i], 0, index);
            if (sub_env == NULL)
                return (-1);
            if (ft_strequ(key, sub_env))
            {
                free(sub_env);
                return (i);
            }
            free (sub_env);
        }
        i++;
    }
    return (-1);
}

void    **realloc_new_env(int env_num)
{
    char **new_env;
    int i;

    i = 0;
    new_env = (char **)malloc(sizeof(char *) * (env_num + 1));
    if (!new_env)
        return (NULL);
    while (g_env_var[i] && i < env_num)
    {
        new_env[i] = ft_strdup(g_env_var[i]);
        i++;
    }
    new_env[env_num] = 0;
    free_old_env(g_env_var);
    return (new_env);
}    

static  char    **remove_env_by_key(int index)
{
    char            *next_env;
    register    int i;

    i = index;
    while (g_env_var[i + 1])
    {
        next_env = ft_strdup(g_env_var[i + 1]);
        free(g_env_var[i]);
        g_env_var[i] = next_env;
        i++;
    }
    return (realloc_new_env(len(g_env_var) - 1));
}

/*
**  unset a bash environment variable
**  unset arg
**  unset arg1 arg2 *
*/

int     unset_builtin(char **args, char *key)
{
    int i;
    int env_index;

    i = 0;
    if (!args[1])
        return (1);
    while (args[++i])
    {
        env_index = find_env(key);
        if (env_index != -1)
           g_env_var = remove_env_by_key(index);
        else
        {
            if (!ft_isalpha)
            {
                write (2, "unset: `", 8);
                write (2, args[i], ft_strlen(args[i]));
                write (2, "': not a valid identifier\n", 26);
            }
        }
    }
    return (1);
}