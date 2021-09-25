/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:05:02 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/24 11:23:33 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_children(void)
{
	int		status;
	int		signal;

	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			g_global->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			signal = WTERMSIG(status);
			if (signal == 13)
				g_global->exit_status = 0;
			else
				g_global->exit_status = signal + 128;
		}		
	}
}

char	**get_path(void)
{
	char	**path;
	char	*tmp;
	int		ret;

	ret = find_env("PATH", g_global->env_var);
	printf ("ret %d\n", ret);
	if (ret == -1)
		return (NULL);
	tmp = return_value(g_global->env_var[ret], '=');
	path = ft_split(g_global->env_var[ret], ':');
	if (!path)
		return (NULL);
	return (path);
}

int	dup_env_var(char **env)
{
	int	i;

	i = -1;
	g_global->env_var = (char **)malloc(sizeof(char *) * (len(env) + 1));
	if (g_global->env_var == NULL)
		exit(EXIT_FAILURE);
	while (++i < len(env))
		g_global->env_var[i] = ft_strdup(env[i]);
	g_global->env_var[i] = 0;
	i = -1;
	g_global->env_ = (char **)malloc(sizeof(char *) * (len(env) + 1));
	if (g_global->env_ == NULL)
		exit(EXIT_FAILURE);
	while (++i < len(env))
		g_global->env_[i] = ft_strdup(env[i]);
	g_global->env_[i] = 0;
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
		check_for_heredoc(m, cmd);
		exec_single_cmd(cmd, m);
	}
	else
	{
		exec_multiple_cmd(cmd, m);
	}
	// free_m(m, cmd->nbr_cmd);
	return (1);
}
