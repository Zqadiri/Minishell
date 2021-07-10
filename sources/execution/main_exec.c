    /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:05:02 by zqadiri           #+#    #+#             */
/*   Updated: 2021/06/07 20:02:03 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_path(void)
{
	char	**path;
	char	*tmp;
	int		ret;

	if ((ret = find_env("PATH")) == -1)
		return (NULL);
	tmp = ft_strdup(g_global->env_var[ret]);
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

	i = 0;
	g_global->env_var = (char **)malloc(sizeof(char *) * (len(env) + 1));
	if (g_global->env_var == NULL)
		exit(EXIT_FAILURE);
	while (env[i] && g_global->env_var[i])
	{
		g_global->env_var[i] = ft_strdup(env[i]);
		i++;
	}
	g_global->env_var[i] = 0;
	return (1);
}

int		exec_single_cmd(t_cmd *cmd)
{
	char	**path;

	if (check_builtin(cmd))
		return (1);
	path = get_path();
	// find_path ()
	return (1);
}

void	execution(t_cmd *cmd, char **env)
{
	(void)env;
	if (cmd->type == eof)
	{
		printf ("%d\n", cmd->redir_nbr);
		exec_single_cmd(cmd);
	}
}

