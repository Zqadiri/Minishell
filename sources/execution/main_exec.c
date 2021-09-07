/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:05:02 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/07 18:50:48 by zqadiri          ###   ########.fr       */
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
			if (signal == SIGQUIT)
				ft_putstr_fd("quit!", 1);
			g_global->exit_status = signal + 128;
		}		
	}
}

char	**get_path(void)
{
	char	**path;
	char	*tmp;
	int		ret;
	int		size;
	int		i;

	i = 0;
	ret = find_env("PATH");
	size = ft_strlen(g_global->env_var[ret]) + 1;
	if (ret == -1)
		return (NULL);
	tmp = (char *)malloc(size * sizeof(char));
	if (tmp == NULL)
		return (NULL);
	while (g_global->env_var[ret][i] != '\0')
	{
		tmp[i] = g_global->env_var[ret][i];
		i++;
	}
	tmp[i] = '\0';
	tmp = return_value(tmp, '=');
	path = ft_split(tmp, ':');
	if (!path)
		return (NULL);
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

void	free_m(t_data *m, int nbr_cmd)
{
	int	i = 0;
	int j = 0;

	while (j < nbr_cmd)
	{
		i = 0;
		while(m[j].path[i] != NULL)
		{
			free(m[j].path[i]);
			m[j].path[i] = NULL;
			i++;
		}
		free(m[j].redir);
		free(m[j].path);
		j++;
	}
	j = 0;
	while (j < nbr_cmd - 1)
	{
		i = 0;
		while(m[j].pipe_fd[i] != NULL)
		{
			free(m[j].pipe_fd[i]);
			m[j].pipe_fd[i] = NULL;
			i++;
		}
		free (m[j].pipe_fd);
		j++;
	}
	free (m);
	m = NULL;
}

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
	free_m(m, cmd->nbr_cmd);
	return (1);
}
