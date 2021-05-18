/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 10:43:52 by zqadiri           #+#    #+#             */
/*   Updated: 2021/05/18 14:16:58 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**  Change the working directoy and updates the environment variable
**  accordingly while handling errors
**  cases : cd ~ | cd --> home dir
**  cd . leave the user in the same directory
**  cd ..
*/

char	*return_value(const char *s, int c)
{
	char	*str;
	char	val;
	int		i;

	i = ft_strlen(s);
	str = (char *)s;
	val = (char)c;
	while (i >= 0)
	{
		if (*str == val)
		{
			str++;
			return (str);
		}
		str++;
		i--;
	}
	return (NULL);
}

char    *get_env_var_by_key(char *key)
{
	int     index;
	char    *value;
	int     i;

	value = NULL;
	index = 0;
	i = 0;
	if (!key)
		return (NULL);
	index = find_env(key);
	if (index == -1)
		return (NULL);
	value = return_value(g_env_var[index], '=');
	return (value);
}

int    set_env_var(char *key, char *new_path)
{
	int		index;
	char	*tmp;

	tmp = NULL;
	if (!key || !new_path)
		return (0);
	index = find_env(key);
	if (index == -1)
		return (1); // OLDPWD not set
	else
	{
		tmp = ft_strjoin(key, "=");
		tmp = ft_strjoin(tmp, new_path);
		free(g_env_var[index]);
        g_env_var[index] = tmp;
	}
	return (1);
}

int change_dir(char *path)
{
    char *current_dir;
    char *buf;
    int size;

    size = 100;
	current_dir = NULL;
    buf = (char *)malloc((size_t)size);
    if (buf == NULL)
		return (0);
    current_dir = getcwd(buf, (size_t)size);
    if (!chdir(path))
    {
        set_env_var("OLDPWD", current_dir);
	    current_dir = getcwd(buf, (size_t)size);
        set_env_var("PWD", current_dir);
        return (1);
    }
    else
    {
        printf("cd: %s: %s\n", path, strerror(errno));
        return (1);
    }
}

int cd_builtin(char *arg)
{
	char *home_path;

	home_path = NULL;
	if (arg[2])
	{
	 	ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);       
	}
	if (!arg || ft_strequ(arg, "~") || ft_strequ(arg, "--"))
	{
		home_path = get_env_var_by_key("HOME");
		if (home_path == NULL)
		{
        	ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		change_dir(home_path);
	}
	else if (ft_strequ(arg, "-"))
	{
		home_path = get_env_var_by_key("OLDPWD");
		change_dir(home_path);
		return (1);
	}
	else
		change_dir(arg);
	return (1);
}

// int     main(int argc, char **argv, char **env)
// {
// 	(void)argc;
// 	dup_env_var(env);
// 	cd_builtin(argv[1]);
// 	env_builtin();
// 	return (1);
// }
