/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 11:42:45 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/07 18:22:43 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Check if the cmd is builtin return 1 if the true
*/

int	is_builtin(t_cmd *cmd)
{
	char	**args;

	args = cmd->argvs;
	if ((ft_strequ(args[0], "pwd")) || (ft_strequ(args[0], "echo")) || \
	(ft_strequ(args[0], "env")) || (ft_strequ(args[0], "exit")) || \
	(ft_strequ(args[0], "export")) || (ft_strequ(args[0], "unset")) || \
	(ft_strequ(args[0], "cd")))
		return (1);
	return (0);
}

/*
** Find the @cmd path in @path
*/

char	*find_path(char	*cmd, char **path)
{
	char	*temp;
	char	*possible_path;
	char	*pfree;
	int		i;
	int		fd;

	i = -1;
	fd = 0;
	if (path == NULL)
		return (NULL);
	while (path[++i])
	{
		pfree = temp;
		temp = ft_strjoin(path[i], "/");
		// free(pfree);
		possible_path = ft_strjoin(temp, cmd);
		fd = open(possible_path, O_RDONLY);
		if (fd >= 0)
			return (possible_path);
	}
	return (NULL);
}

/*
** Open all pipes needed
*/

int	pipe_all(t_cmd *cmd, t_data *m)
{
	int	i;

	i = 0;
	m->pipe_fd = (int **)malloc(sizeof(int *) * cmd->nbr_cmd - 1);
	while (i < cmd->nbr_cmd - 1)
	{
		m->pipe_fd[i] = (int *)malloc(sizeof(int) * 2);
		if (pipe(m->pipe_fd[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
** Close all pipes fds
*/

void	close_all_pipes(int **fd, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
}

/*
** Init t_data structure 
*/

void	init_m(t_data *m)
{
	m->saved_stdout = dup(1);
	m->saved_stdin = dup(0);
	m->path = get_path();
	m->pid = 0;
	m->in = 0;
	m->redir = (t_red *)malloc(sizeof(t_red));
	m->redir->infile = 0;
	m->redir->outfile = 0;
	m->redir->err = 0;
}