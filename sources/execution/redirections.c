/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 16:28:20 by zqadiri           #+#    #+#             */
/*   Updated: 2021/08/28 12:28:50 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count(t_cmd *cmd, t_token_type type)
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
	int	fd;

	i = 0;
	while (i < cmd->redir_nbr)
	{
		if (cmd->r[i].type == less)
		{
			fd = open(cmd->r[i].filename, O_RDWR);
			m->redir->infile = fd;
			if (fd < 0)
			{
				m->redir->err = 1;
				print_error(cmd->r[i].filename);
			}
		}
		i++;
	}
	if (!m->redir->err)
		dup2(m->redir->infile, 0);
}

void	setup_outfiles(t_cmd *cmd, t_data *m)
{
	int i;
	int j;
	int fd;

	i = 0;
	j = 0;
	while (i < cmd->redir_nbr)
	{
		if (cmd->r[i].type == great)
		{
			fd = open(cmd->r[i].filename, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
			m->redir->outfile = fd;
			if (fd < 0)
			{
				m->redir->err = 1;
				print_error(cmd->r[i].filename);
				exit(1);
			}
			j++;
		}
		else if (cmd->r[i].type == greater)
		{
			fd = open(cmd->r[i].filename, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
			m->redir->outfile = fd;
			if (fd < 0)
			{
				m->redir->err = 1;
				print_error(cmd->r[i].filename);
				exit(1);
			}
			j++;
		}
		i++;
	}
	if (!m->redir->err)
		dup2(m->redir->outfile, 1);
}

int		setup_redirections(t_cmd *cmd, t_data *m)
{
	int	i;

	i = 0;
	if (count(cmd, less) != 0)
		setup_infiles(cmd, m);
	if (((count(cmd, great) != 0) || (count(cmd, greater)) != 0) && !m->redir->err)
		setup_outfiles(cmd, m);
	return (1);	
}

/*
**	exec_single_cmd() executes single commands , 
**	commands with redirections and no pipes
*/

void		exec_single_cmd(t_cmd *cmd, t_data *m)
{
	char *possible_path;
	pid_t	child_pid;
	int		status;

	possible_path = NULL;
	setup_redirections(cmd, m);
	if (is_builtin(cmd) && !m->redir->err)
	{
		check_builtin(cmd);
		restore_std(m->saved_stdout, m->saved_stdin);
		return;
	}
	else
	{
		child_pid = fork();
		if (child_pid < 0)
		{
			write (2, "Fork failed !\n", 14);
			return ;	
		}
		if (child_pid == 0)
		{
			if (!ft_strcmp(cmd->argvs[0], "\0"))
				exit(0);
			possible_path = find_path (cmd->argvs[0], m->path);
			if (possible_path == NULL)
				possible_path = ft_strdup(cmd->argvs[0]);
			int fd = open(possible_path, O_RDONLY);
			if (fd < 0)
			{
				write (2, "minishell: ", 11);
				write(2, possible_path, ft_strlen(possible_path));
				ft_putendl_fd(": command not found", 2);
				exit (0);
			}
			if (execve (possible_path, cmd->argvs, g_global->env_var))
				exit(1);		
		}
		else
		{
			waitpid(child_pid, &status, WCONTINUED);
			restore_std(m->saved_stdout, m->saved_stdin);
		}
	}
}

/*
** execute_regular_cmd() executes regular command, commands with no
** redirections oe pipes
*/

int			execute_regular_cmd(t_cmd *cmd)
{
	int child_pid;
	int status;
	pid_t thisChPID;

	if (is_builtin(cmd))
	{
		check_builtin(cmd);
		return (1);
	}
	else
	{
		child_pid = fork();
		if(child_pid < 0 )
		{
			fprintf(stderr, "Fork fails: \n");
			return 1;
		}
		else if(child_pid==0)
		{
			execve(cmd->argvs[0], cmd->argvs,0);
			return 1;
		}
		else if(child_pid > 0)
		{
			do {
				thisChPID = waitpid(child_pid, &status, WUNTRACED | WCONTINUED);
				if (thisChPID == -1) {
					perror("waitpid");
					exit(EXIT_FAILURE);
				}
				if (WIFEXITED(status)) {
					printf("exited, status=%d\n", WEXITSTATUS(status));
					return 0;
				} 
				// else if (WIFSIGNALED(status)) {
				// 	printf("killed by signal %d\n", WTERMSIG(status));
				// } else if (WIFSTOPPED(status)) {
				// 	printf("stopped by signal %d\n", WSTOPSIG(status));
				// } else if (WIFCONTINUED(status)) {
				// 	printf("continued\n");
				// }
			}
			while (!WIFEXITED(status) && !WIFSIGNALED(status));
			return 0;
		}
	}
	return (1);
}
