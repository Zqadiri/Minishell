/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 10:54:16 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/24 10:55:01 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_free(t_data *m, int nbr_cmd)
{
	int	i;

	i = 0;
	if (nbr_cmd == 1)
		return (1);
	while (i < nbr_cmd - 1)
	{
		free(m->redir->pipe_fd[i]);
		i++;
	}
	free(m->redir->pipe_fd);
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

	i = 0;
	while (i < cmd->nbr_cmd)
	{
		if (m[i].path != NULL)
			free_path (m[i].path);
		free(m[i].redir);
		i++;
	}
	free(m);
}

void	main_free(t_data *m, t_cmd *cmd)
{
	int	i;

	if (cmd->nbr_cmd == 1)
	{
		i = 0;
		if (m->path != NULL)
		{
			while (m->path[i])
			{
				free (m->path[i]);
				m->path[i] = NULL;
				i++;
			}
			free(m->path);
			m->path = NULL;
		}
		free(m->redir);
		m->redir = NULL;
		free (m);
		m = NULL;
	}
	else
		free_m(m, cmd);
}

void	ft_freeptr(void *ptr)
{
	free(ptr);
	ptr = NULL;
}
