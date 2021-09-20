/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 19:03:48 by zqadiri           #+#    #+#             */
/*   Updated: 2021/07/16 19:03:48 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static int	add_var_to_env(char *key, char *new_path)
{
	int		index;
	char	*tmp;
	char	*pfree;

	tmp = NULL;
	if (!key || !new_path)
		return (0);
	index = find_env(key, g_global->env_var);
	if (index == -1)
		return (1);
	else
	{
		tmp = ft_strjoin(key, "=");
		pfree = tmp;
		tmp = ft_strjoin(tmp, new_path);
		free (pfree);
		pfree = g_global->env_var[index];
		g_global->env_var[index] = tmp;
		free (pfree);
	}
	return (1);
}

static int	move_to_dir(char *path)
{
	int			ret;
	char		*old_pwd;
	char		*tmp;

	tmp = NULL;
	old_pwd = get_env_var_by_key("PWD");
	add_var_to_env("OLDPWD", old_pwd);
	ret = chdir(path);
	get_pwd(&tmp);
	if (!tmp && (!ft_strcmp(".", path) || !ft_strcmp("./", path)))
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		printf("%s\n", strerror(errno));
		free (tmp);
		tmp = get_env_var_by_key("PWD");
		tmp = add_char_to_word(tmp, '/');
		old_pwd = tmp;
		tmp = ft_strjoin(tmp, path);
		add_var_to_env("PWD", tmp);
		g_global->exit_status = 0;
		return (1);
	}
	else
		return (add_var_to_env("PWD", tmp));
	return (ret);
}

static int	change_dir(char *path, int i, char **argv)
{
	DIR		*dir;

	dir = opendir(path);
	if (!dir)
		return (error_path("cd", argv[i + 1], errno));
	else
	{
		closedir(dir);
		if (move_to_dir(path) == -1)
			return (error_path("cd", argv[i + 1], errno));
	}
	return (1);
}

static int	exec_cd(char *path, int i, char **argv)
{
	char	*pwd;

	if (change_dir(path, i, argv))
		return (1);
	pwd = get_env_var_by_key("PWD");
	add_var_to_env("PWD", pwd);
	free (pwd);
	return (0);
}

int	cd_builtin(char **argv)
{
	char	*path;
	int		i;

	i = 0;
	g_global->exit_status = 0;
	if (argv[i + 1] == NULL)
	{
		path = get_env_var_by_key("HOME");
		if (!argv[i++] && ft_strlen_new(path) == 0)
		{
			g_global->exit_status = 1;
			ft_putstr_fd ("HOME PATH NOT SET", 2);
			return (-1);
		}
	}
	else
		path = ft_strdup(argv[i + 1]);
	exec_cd(path, i, argv);
	free(path);
	return (0);
}
