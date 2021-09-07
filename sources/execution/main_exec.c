/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:05:02 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/07 11:44:01 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_path(void)
{
	char	**path;
	char	*tmp;
	int		ret;

	ret = find_env("PATH");
	if (ret == -1)
		return (NULL);
	tmp = ft_strdup(g_global->env_var[ret]);
	tmp = return_value(tmp, '=');
	path = ft_split(tmp, ':');
	if (!path)
	{
		free(tmp);
		return (NULL);
	}
	return (path);
}

int	dup_env_var(char **env)
{
	int	i;

	i = 0;
	g_global->env_var = (char **)malloc(sizeof(char *) * (len(env) + 1));
	if (g_global->env_var == NULL)
		exit(EXIT_FAILURE);
	while (env[i])
	{
		g_global->env_var[i] = ft_strdup(env[i]);
		i++;
	}
	g_global->env_var[i] = 0;
	return (1);
}

void	restore_std(int saved_stdout, int saved_stdin)
{
	dup2(saved_stdout, 1);
	dup2(saved_stdin, 0);
	close(saved_stdout);
	close(saved_stdin);
}

/*
** main function
*/

int	execution(t_cmd *cmd)
{
	t_data	*m;

	m = (t_data *)malloc(sizeof(t_data) * cmd->nbr_cmd);
	if (cmd->redir_nbr == 0 && cmd->type == eof)
	{
		init_m(m);
		execute_regular_cmd(cmd, m);
	}
	else if (cmd->type == eof && cmd->redir_nbr > 0)
	{
		init_m(m);
		exec_single_cmd(cmd, m);
	}
	else
		exec_multiple_cmd(cmd, m);
	return (1);
}
