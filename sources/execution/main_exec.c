/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:05:02 by zqadiri           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/05/22 10:14:45 by zqadiri          ###   ########.fr       */
=======
/*   Updated: 2021/05/21 21:41:12 by iidzim           ###   ########.fr       */
>>>>>>> c5b323211e82d275ee43a9b66a589a905c22a7b7
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int echo_builtin(char **arg)
{
	(void)arg;

	return (1);
}

int export_builtin(char **arg)
{
	(void)arg;
	
	return (1);
}

char	**get_path(void)
{
	char	**path;
	char	*tmp;
	int		ret;

	if ((ret = find_env("PATH")) == -1)
		return (NULL);
	tmp = ft_strdup(g_env_var[ret]);
	tmp = return_value(tmp, '=');
	if (!(path = ft_split(tmp, ':')))
	{
		free(tmp);
		return (NULL);
	}
	return (path);
}

int		dup_env_var(char **env)
{
	int i;

	i = -1;
	g_env_var = (char **)malloc(sizeof(char *) * (len(env) + 1));
	if (g_env_var == NULL)
		exit(EXIT_FAILURE);
	g_env_var[len(env)] = 0;
	while (env[++i])
	{
		if (!(g_env_var[i] = ft_strdup(env[i])))
			quit();
	}
	return (1);
}

int	launch(char **env, char **arg)
{	
	int i;
	pid_t pid;

	i = 0;
	pid = fork();
	dup_env_var(env);
	if (arg == NULL)
		return (1);
	// if (pid == 0)
	// {
	// 	//child	process
	// }
	// else if (pid < 0)
	// {
	// 	//fail
	// }
	// else
	// {
	// 	//parent process
	// }
	return (1);
}

// int		main(int argc, char  **argv, char **env)
// {
// 	char **args;
// 	char *line;
// 	int r = 0;

<<<<<<< HEAD
	(void)argc;
	(void)argv;
	dup_env_var(env);
	while (1)
	{
		line = malloc(sizeof(char) * 1024);
		if (!line)
			return(-1);
		r = read(0, line, 1023);
		line[r] = '\0';
		args = ft_split(line, ' ');
		int i = 0;
		while (args[i])
		{
			printf ("[%s]\n", args[i]);
			i++;
		}
		check_builtin(args);
	}
	// char **path = get_path();
	// while (path[r])
	// {
	// 	ft_putendl_fd(path[r], 1);
	// 	r++;
	// }
	return (1);
}
=======
// 	(void)argc;
// 	(void)argv;
// 	dup_env_var(env);
// 	while (1)
// 	{
// 		line = malloc(sizeof(char) * 1024);
// 		if (!line)
// 			return(-1);
// 		r = read(0, line, 1023);
// 		line[r] = '\0';
// 		args = ft_split(line, ' ');
// 		int i = 0;
// 		while (args[i])
// 		{
// 			printf ("[%s]\n", args[i]);
// 			i++;
// 		}
// 		check_builtin(args);
// 	}
// 	// char **path = get_path();
// 	// while (path[r])
// 	// {
// 	// 	ft_putendl_fd(path[r], 1);
// 	// 	r++;
// 	// }
// 	return (1);
// }
>>>>>>> c5b323211e82d275ee43a9b66a589a905c22a7b7
