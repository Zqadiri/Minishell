/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:05:02 by zqadiri           #+#    #+#             */
/*   Updated: 2021/05/15 18:31:40 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** List of builtin commands 
*/
char *g_builtin[] = {
  "cd",
  "echo",
  "env",
  "help"
};

/*
** their corresponding functions
*/
int (*g_builtin_func[]) (char **) = {
  &cd_builtin,
  &echo_builtin,
  &env_builtin,
  &exit_builtin
};

int cd_builtin(char **arg)
{
	(void)arg;
	return (1);
}

int echo_builtin(char **arg)
{
	(void)arg;

	return (1);
}

int env_builtin(char **arg)
{
	(void)arg;
	return (1);
}

int exit_builtin(char **arg)
{
	(void)arg;
	return (1);	
}

/*
** Main funtion
*/

int		get_env_var(char **env)
{
	(void)env;
	return (1);
}

int	get_built_num(void)
{
  return sizeof(g_builtin) / sizeof(char *);
}


int	launch(char **env, char **arg)
{	
	int i;
	int num_builtin;

	i = 0;
	num_builtin = get_built_num();
	get_env_var(env);
	if (arg == NULL)
		return (1);
	while (i < num_builtin)
	{
		if (strcmp(arg[0], g_builtin[i]) == 0)
			return (*g_builtin_func[i])(arg);
		i++;
	}
	return (1);
}
