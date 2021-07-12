/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 16:28:20 by zqadiri           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/07/12 12:15:03 by iidzim           ###   ########.fr       */
=======
/*   Updated: 2021/07/12 11:46:37 by zqadiri          ###   ########.fr       */
>>>>>>> c2f5352d5b3c440e6e030019901396ec5e0d4cdd
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

void	setup_infiles(t_cmd *cmd, t_data *m)
{
	int i;
	int	bad_infile;

	i = 0;
	bad_infile = 0;
	m->redir->infile_fds = malloc(sizeof(int) * m->redir->less_cpt);
	while (i < cmd->redir_nbr)
	{
		if (cmd->r[i].type == less)
		{
			m->redir->infile_fds[i] = open(cmd->r[i].filename, O_RDWR);
			if (m->redir->infile_fds[i] < 0)
			{
				bad_infile = 1;
				print_error(cmd->r[i].filename);
			}
		}
		i++;
	}
	if (!bad_infile)
		dup2(m->redir->infile_fds[m->redir->less_cpt - 1], 0);
}

void	setup_outfiles(t_cmd *cmd, t_data *m)
{
	int i;
    int j;
	int	bad_outfile;
	int nbr;

	i = 0;
    j = 0;
	bad_outfile = 0;
	nbr = m->redir->greater_cpt + m->redir->great_cpt;
	m->redir->outfile_fds = malloc(sizeof(int) * (nbr));
	while (i < cmd->redir_nbr)
	{
		if (cmd->r[i].type == great)
		{
			m->redir->outfile_fds[j] = open(cmd->r[i].filename, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
			if (m->redir->outfile_fds[j] < 0)
			{
				bad_outfile = 1;
				print_error(cmd->r[i].filename);
				exit(1);
			}
            j++;
		}
		else if (cmd->r[i].type == greater)
		{
			m->redir->outfile_fds[j] = open(cmd->r[i].filename, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
			if (m->redir->outfile_fds[j] < 0)
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
		dup2(m->redir->outfile_fds[nbr - 1], 1);
}

int		setup_redirections(t_cmd *cmd, t_data *m)
{
	int	i;

	i = 0;
	init_redir(cmd, m->redir);
	if (m->redir->less_cpt != 0)
		setup_infiles(cmd, m);
	if ((m->redir->great_cpt != 0 )|| (m->redir->greater_cpt != 0))
		setup_outfiles(cmd, m);
	return (1);	
}

// ? check builtin

void		exec_single_cmd(t_cmd *cmd, t_data *m)
{
	char 	*possible_path;

	if (cmd->redir_nbr != 0)
		setup_redirections(cmd, m);
	if (check_builtin(cmd))
		return ;
	else
	{
		possible_path = find_path (cmd->argvs[0], m->path);
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

