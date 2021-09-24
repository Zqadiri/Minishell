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
		free(m->pipe_fd[i]);
		i++;
	}
	free(m->pipe_fd);
	return (1);
}

void	free_m(t_data *m, int nbr_cmd)
{
	int	i;
	int	j;

	j = -1;
	while (++j < nbr_cmd)
	{
		i = -1;
		if (m[j].path == NULL)
			break ;
		while (m[j].path[++i] != NULL)
		{
			free(m[j].path[i]);
			m[j].path[i] = NULL;
		}
		free(m[j].path);
	}
	j = -1;
	while (++j < nbr_cmd)
		free(m[j].redir);
	pipe_free(m, nbr_cmd);
	free (m);
	m = NULL;
}
