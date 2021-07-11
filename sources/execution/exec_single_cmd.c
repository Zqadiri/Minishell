/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 16:28:20 by zqadiri           #+#    #+#             */
/*   Updated: 2021/07/11 19:03:40 by iidzim           ###   ########.fr       */
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
    int j;
	int	bad_outfile;
	int nbr;

	i = 0;
    j = 0;
	bad_outfile = 0;
	nbr = redir->greater_cpt + redir->great_cpt;
	redir->outfile_fds = malloc(sizeof(int) * (nbr));
	while (i < cmd->redir_nbr)
	{
		printf ("fd: %d\n", nbr);
		if (cmd->r[i].type == great)
		{
            // printf ("is in\n");
			redir->outfile_fds[j] = open(cmd->r[i].filename, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
			if (redir->outfile_fds[j] < 0)
			{
				bad_outfile = 1;
				print_error(cmd->r[i].filename);
				exit(1);
			}
            j++;
		}
		else if (cmd->r[i].type == greater)
		{
			redir->outfile_fds[j] = open(cmd->r[i].filename, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
			if (redir->outfile_fds[j] < 0)
			{
				bad_outfile = 1;
				print_error(cmd->r[i].filename);
				exit(1);
			}
            j++;
		}
		i++;
	}
	if (!bad_outfile)
		dup2(redir->outfile_fds[nbr - 1], 1);
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

// ? check builtin

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

//! minishell-1.0> /bin/wechohe
//? new REPL without error message

//! cd not working

//!echo -nnnnnnnnnnnnnnnnnnnnnf bonjour\0000
//? must print iin newline

//!export

//! <Makefile < wrong_file cat
//? minishell-1.0: wrong_file : No such file or directory + infinite loop
//? minishell-1.0: wrong_file : Permission denied + infinite loop

