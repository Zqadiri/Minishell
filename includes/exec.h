/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 15:03:30 by zqadiri           #+#    #+#             */
/*   Updated: 2021/07/11 12:29:00 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <signal.h>
# include "lexer.h"

typedef struct s_redir
{
	t_token_type	type;
	char			*filename;
}					t_redir;

typedef struct s_cmd
{
	int				nbr_cmd;
	int				args_size;
	char			**argvs;
	int				redir_nbr;
	t_redir			*r;
	t_token_type	type;
}               t_cmd;

typedef struct s_red
{
	int		*infile_fds;
	int		*outfile_fds;
	int		less_cpt;
	int		great_cpt;
	int		greater_cpt;
}	t_red;

/*
** Function Declarations for builtin shell commands
*/

int		cd_builtin(char **arg);
int		echo_builtin(char **arg);
int		pwd_builtin(void);
int		env_builtin(void);
void	exit_builtin(char **arg);
int		unset_builtin(char **args);
int		export_builtin(char **arg);

/*
** Utils
*/

int		quit(void);
int		len(char **env);
int		alpha(char *key);
int		dup_env_var(char **env);
char	**dup_env(void);
char	**get_path(void);
void	print_sorted_env(char **sorted_env);
char	**realloc_new_env(int env_num);
int		set_env_var(char *key, char *new_path);

/*
** Helpers 
*/

void	set_new_env(char *arg);
int		env_count(void);
int		find_env(char *key);
char	*get_env_var_by_key(char *key);
char	*return_value(const char *s, int c);
int		get_str_by_char(char *str, char c);
void	modify_env(char *arg, char *key);

/*
** Signals
*/

int		check_signals(void);

#endif
