/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:05:02 by zqadiri           #+#    #+#             */
/*   Updated: 2021/07/11 14:44:26 by zqadiri          ###   ########.fr       */
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
	write (2, "minishell-1.0: ", 15);
	write(2, file_error, ft_strlen(file_error));
	perror(" ");
}

void	setup_infiles(t_cmd *cmd, t_red *redir)
{
	int i;
	int	bad_infile;

	i = 0;
	bad_infile = 0;
	redir->infile_fds = malloc(sizeof(int) * redir->less_cpt);
	while (i < cmd->redir_nbr)
	{
		if (cmd->r[i].type == less)
		{
			// printf (" -- >%d\n", redir->less_cpt);	
			redir->infile_fds[i] = open(cmd->r[i].filename, O_RDWR);
			if (redir->infile_fds[i] < 0)
			{
				bad_infile = 1;
				print_error(cmd->r[i].filename);
			}
		}
		i++;
	}
	if (!bad_infile)
	{
		// printf ("bad : %d\n", bad_infile);
		printf ("fd : %d\n", redir->infile_fds[redir->less_cpt - 1]);
		dup2(redir->infile_fds[redir->less_cpt - 1], 0);
		// close(redir->infile_fds[redir->less_cpt - 1]);
	}
}

void	setup_outfiles(t_cmd *cmd, t_red *redir)
{
	int i;
	int	bad_outfile;
	int nbr;

	i = 0;
	bad_outfile = 0;
	nbr = redir->greater_cpt + redir->great_cpt;
	redir->outfile_fds = malloc(sizeof(int) * (nbr + 1));
	while (i < cmd->redir_nbr)
	{
		printf("type :%d\n", cmd->r[0].type);
		if (cmd->r[i].type == great)
		{
			printf (" -- >%d\n", i);	
			redir->outfile_fds[i] = open(cmd->r[i].filename, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
			if (redir->outfile_fds[i] < 0)
			{
				bad_outfile = 1;
				print_error(cmd->r[i].filename);
			}
		}
		else if (cmd->r[i].type == greater)
		{
			printf (" -- >%d\n", i);	
			redir->outfile_fds[i] = open(cmd->r[i].filename, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
			if (redir->outfile_fds[i] < 0)
			{
				bad_outfile = 1;
				print_error(cmd->r[i].filename);
			}
		}
		i++;
	}
	if (!bad_outfile)
	{
		printf ("out_fd : %d\n", redir->outfile_fds[nbr]);
		// ? dup2
		dup2(redir->outfile_fds[nbr], 1);
	}
}

int		setup_redirections(t_cmd *cmd, t_red *redir)
{
	int		i;

	i = 0;
	init_redir(cmd, redir);
	if (redir->less_cpt != 0)
		setup_infiles(cmd, redir);
	if (redir->great_cpt != 0 || redir->greater_cpt != 0)
		setup_outfiles(cmd, redir);
	return (1);	
}

int		exec_single_cmd(t_cmd *cmd, t_red *redir)
{
	char	**path;
	char 	*possible_path;

	path = get_path();
	setup_redirections(cmd, redir);
	if (check_builtin(cmd))
		return (1);
	else
	{
		possible_path = find_path (cmd->argvs[0], path);
		execve (possible_path, cmd->argvs, g_global->env_var);
	}
	return (1);
}

void	execution(t_cmd *cmd, char **env)
{
	(void)env;
	t_red	*redir;

	redir = malloc(sizeof(t_red));
	if (cmd->type == eof)
	{
		// printf ("%d\n", cmd->redir_nbr);
		exec_single_cmd(cmd, redir);
	}
	// close(redir->infile_fds[redir->less_cpt - 1]);
	free (redir);

}

