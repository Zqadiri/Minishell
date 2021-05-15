/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:05:02 by zqadiri           #+#    #+#             */
/*   Updated: 2021/05/15 17:31:26 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** List of builtin commands 
*/
char *g_builtin_str[] = {
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

int		launch(char **env)
{
	int i = 0;
	while (env[i])
	{
		printf ( "%s\n", env[i]);
		i++;
	}
	
	return (1);
}
