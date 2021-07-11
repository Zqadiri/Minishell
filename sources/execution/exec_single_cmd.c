/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 16:28:20 by zqadiri           #+#    #+#             */
/*   Updated: 2021/07/11 16:41:41 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
		dup2(redir->infile_fds[redir->less_cpt - 1], 0);
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
		if (cmd->r[i].type == great)
		{
			redir->outfile_fds[i] = open(cmd->r[i].filename, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
			if (redir->outfile_fds[i] < 0)
			{
				bad_outfile = 1;
				print_error(cmd->r[i].filename);
				exit(1);
			}
		}
		else if (cmd->r[i].type == greater)
		{
			redir->outfile_fds[i] = open(cmd->r[i].filename, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
			if (redir->outfile_fds[i] < 0)
			{
				bad_outfile = 1;
				print_error(cmd->r[i].filename);
				exit(1);
			}
		}
		i++;
	}
	if (!bad_outfile)
	{
		// printf ("fd: %d\n", redir->outfile_fds[nbr - 1]);
		if (!dup2(redir->outfile_fds[nbr], 1))
			printf("error? \n");
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

void		exec_single_cmd(t_cmd *cmd, t_red *redir)
{
	char	**path;
	char 	*possible_path;

	path = get_path();
	if (cmd->redir_nbr != 0)
		setup_redirections(cmd, redir);
	if (check_builtin(cmd))
		exit(1);
	else
	{
		possible_path = find_path (cmd->argvs[0], path);
		if (possible_path == NULL)
			possible_path = ft_strdup(cmd->argvs[0]);
		execve (possible_path, cmd->argvs, g_global->env_var);
		exit(1);
	}
}