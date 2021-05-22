/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:20:06 by zqadiri           #+#    #+#             */
/*   Updated: 2021/05/22 11:26:26 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void free_old_env()
{
    int i;

    i = 0;
    while (g_env_var[i])
    {
        free(g_env_var[i]);
        g_env_var[i] = NULL;
        i++;
    }
    free (g_env_var);
    g_env_var = NULL;
}

int get_str_by_char(char *str, char c)
{
	char	*ch;

	ch = ft_strchr(str, c);
	if (!ch)
		return (-1);
	return ((int)(ch - str));
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

char    **realloc_new_env(int env_num)
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
    free_old_env();
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

int     unset_builtin(char **args)
{
    int i;
    int env_index;

    i = -1;
    if (!args[1])
        return (1);
    while (args[++i])
    {
        env_index = find_env(args[i]);
        if (env_index != -1)
           g_env_var = remove_env_by_key(env_index);
        else
        {
            if (alpha(args[1]) == -1)
            {
                write (2, "unset: `", 8);
                write (2, args[i], ft_strlen(args[i]));
                write (2, "': not a valid identifier\n", 26);
                break;
            }
        }
    }
    return (1);
}

// int main(int argc, char **argv, char **env)
// {
//     int i = 1;
// 	dup_env_var(env);
//     while (i < argc)
//     {
//         unset_builtin(argv[i]);
//         i++;
//     }
//     env_builtin();
//     return (1);
// }