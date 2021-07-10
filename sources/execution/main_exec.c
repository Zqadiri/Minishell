/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:05:02 by zqadiri           #+#    #+#             */
/*   Updated: 2021/07/10 21:48:11 by zqadiri          ###   ########.fr       */
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

char	*find_path(char	*cmd, char **path)
{
	char	*temp;
	char	*possible_path;
	char	*pfree;
	int		i;
	int		fd;

	i = -1;
	while (path[++i])
	{
		temp = ft_strjoin(path[i], "/");
		pfree = temp;
		possible_path = ft_strjoin(temp, cmd);
		free(temp);
		fd = open(possible_path, O_RDONLY);
		if (fd > 0)
		{
			// *final_path = ft_strdup(possible_path);
			// free(possible_path);
			// possible_path = NULL;
			return (possible_path);
		}
		// free(possible_path);
		// possible_path = NULL;
	}
	return (NULL);
}

int		check_each_type(t_cmd *cmd, t_token_type type)
{
	int	i;
	int j;

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

void	init_redir(t_cmd *cmd, t_red *redir)
{
	redir->infile_fds = NULL;
	redir->outfile_fds = NULL;
	redir->less_cpt = check_each_type(cmd, less);
	redir->great_cpt = check_each_type(cmd, great);
	redir->greater_cpt = check_each_type(cmd, greater);
}

/*
** redirect stdin to read from the pipe
** redirect stdout to outfile_fd 
*/

void	print_error(char *file_error)
{
	write (2, "minishell : ", 7);
	write(2, file_error, ft_strlen(file_error));
	perror(" ");
}

void	setup_infiles(t_cmd *cmd, t_red *redir)
{
	int i;

	i = 0;
	redir->infile_fds = malloc(sizeof(int) * redir->less_cpt);
	while (i < cmd->redir_nbr)
	{
		if (cmd->r->type == less)
		{
			redir->infile_fds[i] = open(cmd->r->filename, O_RDWR);
			if (cmd->r->filename < 0)
			{		
				print_error(cmd->r->filename);
				exit (0);
			}
		}
		i++;
	}
	// dup2(p->outfile_fd, 1);
	// dup2(p->fd[0], 0);
}

int		setup_redirections(t_cmd *cmd)
{
	t_red	*redir;
	int		i;

	i = 0;
	redir = malloc(sizeof(t_red));
	init_redir(cmd, redir);
	if (redir->less_cpt != 0)
		setup_infiles(cmd, redir);
	return (0);
}

int		exec_single_cmd(t_cmd *cmd)
{
	char	**path;
	char 	*possible_path;

	path = get_path();
	if (!cmd->redir_nbr)
	{
		if (check_builtin(cmd))
			return (1);
		else
		{
			possible_path = find_path (cmd->argvs[0], path);
			execve (possible_path, cmd->argvs, g_global->env_var);
		}
	}
	else
		setup_redirections(cmd);
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

