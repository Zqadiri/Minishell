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

#include "../../../incs/minishell.h"

int			ft_strlen(const char *str)
{
	int		len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

char		*add_char_to_word(char *word, char c)
{
	char	*save_word;
	int		new_word_len;

	if (!word)
	{
		if (!(word = (char *)ft_memalloc(sizeof(char) * 2)))
			return (ERROR);
		word[0] = c;
		word[1] = '\0';
		return (word);
	}
	new_word_len = ft_strlen(word) + 2;
	save_word = word;
	if (!(word = (char *)ft_memalloc(sizeof(char) * new_word_len)))
		return (ERROR);
	ft_memcpy(word, save_word, ft_strlen(save_word));
	word[ft_strlen(save_word)] = c;
	return (word);
}

int		get_pwd(char **pwd)
{
	char *new_pwd;

	new_pwd = NULL;
	if (!(new_pwd = (char *)malloc(sizeof(char) * 1025)))
		return (ERROR);
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
	tmp = ft_strjoin("OLDPWD=", old_pwd);
	add_var_to_env(tmp);
    free (tmp);
	ret = chdir(path);
	tmp = get_env_var_by_key("PWD");
	if (!get_pwd(tmp) && (!ft_strcmp(".", path) || !ft_strcmp("./", path)))
	{
		ft_printf(2, "cd: error retrieving current directory: %s%s\n",
			"getcwd: cannot access parent directories: ", strerror(errno));
		tmp = add_char_to_word(tmp, '/');
		old_pwd = tmp;
		tmp = ft_strjoin(tmp, path);
	}
	return (ret);
}

int		error_path(const char *cmd, const char *path, int errnum)
{
	ft_printf(2, "minishell: %s: %s: %s\n",
		cmd, path, strerror(errnum));
	return (1);
}

static int	change_dir(char *path,int i,char **argv)
{
	DIR			*dir;

	dir = opendir(path);
	if (!dir)
		return (error_path("cd", argv[i + 1], errno));
	else
	{
		closedir(dir);
		if (move_to_dir(path) == -1)
			return (error_path("cd", argv[i + 1], errno));
	}
	return (0);
}

static int	exec_cd(char *path,int i,char **arg)
{
	char		*pwd;
	char		*pwd_env;

	if (change_dir(path, i, argv) != 0)
		return (1); // error
	pwd = get_env_var_by_key("PWD");
	pwd_env = ft_strjoin("PWD=", pwd);
	add_var_to_env(pwd_env);
	return (0);
}

int			cd(char **argv)
{
	char		*path;
	int			i;

	i = 0;
	if (len(argv) > 2)
	{
        // arg error
		ft_printf(2, "minishell: cd: to many arguments\n");
		return (1);
	}
	if (!argv[i++])
	{
		path = get_env_var_by_key("HOME");
		if (!argv[i++] && ft_strlen(path) == 0)
		{
            // error path not set
			return (-1);
		}
	}
	else
		path = ft_strdup(argv[i + 1]);
	return (exec_cd(path, i, argv));
}