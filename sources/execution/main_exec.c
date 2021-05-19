/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:05:02 by zqadiri           #+#    #+#             */
/*   Updated: 2021/05/19 11:50:59 by zqadiri          ###   ########.fr       */
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

// 	argv++;
// 	(void)argc;
// 	args = argv;
// 	dup_env_var(env);
// 	char *line;
// 	int r = 0;

// 	//buffersize = 1 -> signels!
// 	line = malloc(sizeof(char) * 1024);
// 	if (!line)
// 		return(NULL);
// 	r = read(0, line, 1023);
// 	return (1);
// }
