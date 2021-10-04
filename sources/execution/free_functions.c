/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 10:54:16 by zqadiri           #+#    #+#             */
/*   Updated: 2021/10/04 20:03:42 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_free(int **pipe_fd, int nbr_cmd)
{
	int	i;

	i = nbr_cmd - 2;
	while (i >= 0)
	{
		free(pipe_fd[i]);
		pipe_fd[i] = NULL;
		i--;
	}
	free(pipe_fd);
	pipe_fd = NULL;
	return (1);
}

static void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free (path[i]);
		path[i] = NULL;
		i++;
	}
	free(path);
	path = NULL;
}

void	free_m(t_data *m, t_cmd *cmd)
{
	int	i;

	i = cmd->nbr_cmd - 1;
	while (i >= 0)
	{
		if (m[i].redir->pipe_fd != NULL)
			pipe_free (m[i].redir->pipe_fd, cmd->nbr_cmd);
		free (m[i].redir);
		i--;
	}
	if (m->state->path != NULL)
		free_path (m->state->path);
	if (m->state->env_ != NULL)
		free_path (m->state->env_);
	free (m->state);
	free(m);
}

void	main_free(t_data *m, t_cmd *cmd)
{
	int	i;

	if (cmd->nbr_cmd == 1)
	{
		i = 0;
		// if (m->state->path != NULL)
		// {
		// 	while (m->state->path[i])
		// 	{
		// 		free (m->state->path[i]);
		// 		m->state->path[i] = NULL;
		// 		i++;
		// 	}
		// 	free(m->state->path);
		// 	m->state->path = NULL;
		// }
		// // free(m->state);
		free(m->redir);
		m->redir = NULL;
		free (m);
		m = NULL;
	}
	// else
	// 	free_m(m, cmd);
}

void	ft_freeptr(void *ptr)
{
	free(ptr);
	ptr = NULL;
}
