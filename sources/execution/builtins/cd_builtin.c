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

#include "../../../includes/minishell.h"

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

static int	add_var_to_env(char *key, char *new_path)
{
	int		index;
	char	*tmp;

	tmp = NULL;
	if (!key || !new_path)
		return (0);
	index = find_env(key);
	if (index == -1)
		return (1);
	else
	{
		tmp = ft_strjoin(key, "=");
		tmp = ft_strjoin(tmp, new_path);
		free(g_global->env_var[index]);
		g_global->env_var[index] = tmp;
	}
	return (1);
}

char		*add_char_to_word(char *word, char c)
{
	char	*save_word;
	int		new_word_len;

	if (!word)
	{
		if (!(word = (char *)ft_memalloc(sizeof(char) * 2)))
			return (NULL);
		word[0] = c;
		word[1] = '\0';
		return (word);
	}
	new_word_len = ft_strlen_new(word) + 2;
	save_word = word;
	if (!(word = (char *)ft_memalloc(sizeof(char) * new_word_len)))
		return (NULL);
	ft_memcpy(word, save_word, ft_strlen_new(save_word));
	word[ft_strlen_new(save_word)] = c;
	return (word);
}

int		get_pwd(char **pwd)
{
	char *new_pwd;

	new_pwd = NULL;
	if (!(new_pwd = (char *)malloc(sizeof(char) * 1025)))
		return (-1);
	ft_bzero(new_pwd, 1025);
	if (getcwd(new_pwd, sizeof(char) * 1024) == NULL)
	{
		free(new_pwd);
		return (0);
	}
	*pwd = new_pwd;
	return (1);
}

static int	move_to_dir(char *path)
{
	int			ret;
	char		*old_pwd;
	char		*tmp;

	old_pwd = get_env_var_by_key("PWD");
	add_var_to_env("OLDPWD", old_pwd);
	ret = chdir(path);
	get_pwd(&tmp);
	if (!tmp && (!ft_strcmp(".", path) || !ft_strcmp("./", path)))
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		printf("%s\n", strerror(errno));
		tmp = get_env_var_by_key("PWD");
		tmp = add_char_to_word(tmp, '/');
		old_pwd = tmp;
		tmp = ft_strjoin(tmp, path);
		add_var_to_env("PWD", tmp);
		return (1);
	}
	else
	{
		add_var_to_env("PWD", tmp);
		return (1);
	}
	return (ret);
}

int		error_path(const char *cmd, const char *path, int errnum)
{
	printf("minishell: %s: %s: %s\n",
		cmd, path, strerror(errnum));
	return (1);
}

static int	change_dir(char *path,int i,char **argv)
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
	return (0);
}

int	cd_builtin(char **argv)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	if (len(argv) > 2)
	{
		ft_putstr_fd("minishell: cd: to many arguments\n", 2);
		return (1);
	}
	if (argv[i + 1] == NULL)
	{
		path = get_env_var_by_key("HOME");
		if (!argv[i++] && ft_strlen_new(path) == 0)
		{
			ft_putstr_fd ("HOME PATH NOT SET", 2);
			return (-1);
		}
	}
	else
		path = ft_strdup(argv[i + 1]);
	return (exec_cd(path, i, argv));
}