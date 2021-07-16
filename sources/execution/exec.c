/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:05:02 by zqadiri           #+#    #+#             */
/*   Updated: 2021/07/16 13:05:42 by zqadiri          ###   ########.fr       */
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
	if (path == NULL)
		return (NULL);
	while (path[++i])
	{
		temp = ft_strjoin(path[i], "/");
		pfree = temp;
		possible_path = ft_strjoin(temp, cmd);
		free(temp);
		fd = open(possible_path, O_RDONLY);
		if (fd > 0)
			return (possible_path);
	}
	return (NULL);
}

void	restore_std(int saved_stdout, int saved_stdin)
{
	dup2(saved_stdout, 1);
	dup2(saved_stdin, 0);
	close(saved_stdout);
	close(saved_stdin);
}


int		is_builtin(t_cmd *cmd)
{
	char	**args;

	args = cmd->argvs;
	if ((ft_strequ(args[0], "pwd")) || (ft_strequ(args[0], "echo")) ||
	(ft_strequ(args[0], "env")) || (ft_strequ(args[0], "env")) ||
	(ft_strequ(args[0], "export")) || (ft_strequ(args[0], "unset")) ||
	(ft_strequ(args[0], "cd")) || (ft_strequ(args[0], "exit")))
		return (1);
	return (0);
}

void	execution(t_cmd *cmd, char **env)
{
	(void)env;
	int		pid;
	t_data	*m;
	int		status;

	// ! single cmd with no builtins 
	m = (t_data *)malloc(sizeof(t_data) * cmd->nbr_cmd); 
	if (cmd->type == eof && !is_builtin(cmd))
	{
		pid = fork();
		if (pid < 0)
			printf("Error\n");
		if (pid == 0)
		{
			init_m(m);
			exec_single_cmd(cmd, m);
		}
		else
		{
			waitpid(pid, &status, WCONTINUED);
			if (cmd->redir_nbr)
				restore_std(m->saved_stdout, m->saved_stdin);
		}
	}
	// ! execve commands
	else if (is_builtin(cmd) && cmd->type == eof)
	{
		init_m(m);
		exec_single_cmd(cmd, m);
		if (cmd->redir_nbr)
			restore_std(m->saved_stdout, m->saved_stdin);		
	}
	else
		exec_multiple_cmd(cmd, m);	
	// free (m);
}

// ! Redo cd 
 
