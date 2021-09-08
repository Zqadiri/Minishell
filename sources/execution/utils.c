/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 15:31:05 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/08 12:06:01 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count(t_cmd *cmd, t_token_type type)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cmd->redir_nbr)
	{
		if (cmd->r[i].type == type)
			j++;
		i++;
	}
	return (j);
}

char	*get_env_var_by_key(char *key)
{
	int		index;
	char	*value;
	int		i;

	value = NULL;
	index = 0;
	i = 0;
	if (!key)
		return (NULL);
	index = find_env(key);
	if (index == -1)
		return (NULL);
	value = return_value(g_global->env_var[index], '=');
	return (value);
}

void	setup_in(t_cmd *cmd, t_data *m)
{
	int	cpt;
	int	fd;

	cpt = (count(cmd, less));
	if (cpt == 0)
	{
		m->redir->infile = 0;
		return ;
	}
	cpt = 0;
	while (cpt < cmd->redir_nbr)
	{
		if (cmd->r[cpt].type == less)
		{
			fd = open(cmd->r[cpt].filename, O_RDWR);
			if (fd < 0)
			{
				print_error(cmd->r[cpt].filename);
				m->redir->err = 1;
				return ;
			}
		}
		cpt++;
	}
	m->redir->infile = fd;
}

void	setup_out(t_cmd *cmd, t_data *m)
{
	int	i;
	int	fd;

	i = 0;
	while (i < cmd->redir_nbr)
	{
		if (cmd->r[i].type == great)
		{
			fd = open(cmd->r[i].filename, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
			if (fd < 0)
			{
				m->redir->err = 1;
				print_error(cmd->r[i].filename);
			}
		}
		else if (cmd->r[i].type == greater)
		{
			fd = open(cmd->r[i].filename, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
			check_valid_fd(m, cmd->r[i].filename, fd);
		}
		i++;
	}
	m->redir->outfile = fd;
}

void	free_m(t_data *m, int nbr_cmd)
{
	int	i;
	int	j;

	j = -1;
	while (++j < nbr_cmd)
	{
		i = -1;
		while (m[j].path[++i] != NULL)
		{
			free(m[j].path[i]);
			m[j].path[i] = NULL;
		}
		free(m[j].redir);
		free(m[j].path);
	}
	j = -1;
	while (++j < nbr_cmd - 1)
	{
		i = -1;
		while (m[j].pipe_fd[++i] != NULL)
			free(m[j].pipe_fd[i]);
		free (m[j].pipe_fd);
	}
	free (m);
	m = NULL;
}
