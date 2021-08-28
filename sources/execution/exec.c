/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:05:02 by zqadiri           #+#    #+#             */
/*   Updated: 2021/08/28 12:30:12 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int
// fork_pipes (int n, struct command *cmd)
// {
//   int i;
//   pid_t pid;
//   int in, fd [2];

//   /* The first process should get its input from the original file descriptor 0.  */
//   in = 0;

//   /* Note the loop bound, we spawn here all, but the last stage of the pipeline.  */
//   for (i = 0; i < n - 1; ++i)
//     {
//       pipe (fd);

//       /* f [1] is the write end of the pipe, we carry `in` from the prev iteration.  */
//       spawn_proc (in, fd [1], cmd + i);

//       /* No need for the write end of the pipe, the child will write here.  */
//       close (fd [1]);

//      // Keep the read end of the pipe, the next child will read from there.  */
//       in = fd [0];
//     }

//   Last stage of the pipeline - set stdin be the read end of the previous pipe
//      and output to the original file descriptor 1. 
//   if (in != 0)
//     dup2 (in, 0);

//   /* Execute the last stage with the current process. */
//   return execvp (cmd [i].argv [0], (char * const *)cmd [i].argv);
// }

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

int		execution(t_cmd *cmd, char **env)
{
	(void)env;
	t_data	*m;

	m = (t_data *)malloc(sizeof(t_data) * cmd->nbr_cmd);
	if (cmd->redir_nbr == 0 && cmd->type == eof)
		execute_regular_cmd(cmd);
	else if (cmd->type == eof && cmd->redir_nbr > 0)
	{
		init_m(m);
		exec_single_cmd(cmd, m);
	}
	else
		exec_multiple_cmd(cmd, m);
	restore_std(m->saved_stdout, m->saved_stdin);
	return (1);
}
