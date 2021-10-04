/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 15:03:30 by zqadiri           #+#    #+#             */
/*   Updated: 2021/10/04 19:49:52 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <term.h>
# include <signal.h>
# include <dirent.h>
# include "lexer.h"

typedef struct s_redir
{
	t_token_type	type;
	char			*filename;
	int				is_quoted;
}					t_redir;

typedef struct s_cmd
{
	int				nbr_cmd;
	int				args_size;
	char			**argvs;
	int				redir_nbr;
	t_redir			*r;
	t_token_type	type;
}	t_cmd;

typedef struct s_red
{
	int				infile;
	int				outfile;
	int				err;
	int				in_heredoc;
	char			*filename_;
	int				**pipe_fd;
}	t_red;

typedef	struct s_state
{
	char			**env_;
	char			**path;
}	t_state;
typedef struct s_data
{
	int				cmd_id;
	int				saved_stdout;
	int				saved_stdin;
	pid_t			pid;
	t_red			*redir;
	t_state			*state;
	int				read_end;
}	t_data;

/*
** Function Declarations for builtin shell commands
*/

int			cd_builtin(char **arg);
int			echo_builtin(char **arg);
int			pwd_builtin(void);
void		add_to_env(char *arg, t_data *m);
int			env_builtin(t_data *m);
int			exit_builtin(char **args);
int			unset_builtin(char **args, t_data *m);
int			export_builtin(char **arg, t_data *m);
char		*add_char_to_word(char *word, char c);
char		*get_pwd(void);
char		*return_value(const char *s, int c);
int			error_path(const char *cmd, const char *path, int errnum);
void		error_exit(char *arg);
long long	atoi_exit(const char *str);

/*
** Error Functions
*/

void		setup_out(t_cmd *cmd, t_data *m, int j);
void		setup_in(t_cmd *cmd, t_data *m, int j);
void		wait_children(void);
void		fork_failed(void);
void		not_valid_id(char *arg);
void		error_retrieving_cd(void);
int			cmdnf_nsfile(t_cmd *cmd, t_data *m, char *possible_path);
int			check_for_permission(t_cmd *cmd);

/*
** Utils
*/

int			env_count(void);
int			dup_env_var(char **env);
char		**dup_env(void);
char		**get_path(void);
void		print_sorted_env(char **sorted_env);
char		**realloc_new_env(int env_num, char *arg, char **env_pointer);
int			set_env_var(char *key, char *new_path);
void		main_free(t_data *m, t_cmd *cmd);

/*
** Helpers 
*/

int			find_env(char *key, char **env_pointer);
char		*get_env_var_by_key(char *key);
char		*return_value(const char *s, int c);
int			get_str_by_char(char *str, char c, int i);
int			is_valid_env_key(char *arg);
void		modify_env(char *arg, char *key);
int			is_builtin(t_cmd *cmd);
int			pipe_all(t_cmd *cmd, t_data *m);
void		restore_std(int saved_stdout, int saved_stdin);
void		exec_cmd_path(t_cmd *cmd, t_data *m, int *p_fd);
void		check_valid_fd(t_data *m, char *file_error, int fd);
void		find_cmd_path(t_cmd *cmd, t_data *m);

/*
** main
*/

void		check_for_heredoc(t_data *m, t_cmd *cmd);
int			check_signals(void);
char		*find_path(char	*cmd, char **path);
void		exec_multiple_cmd(t_cmd *cmd, t_data *m, t_state *state);
int			is_builtin(t_cmd *cmd);
void		init_m(t_data *m, int i, t_state *state);
void		print_error(char *file_error);
int			count(t_cmd *cmd, t_token_type type);
void		exec_simple_pipe(t_cmd *cmd, t_data *m, t_state *state);
void		exec_single_cmd(t_cmd *cmd, t_data *m);
int			execute_regular_cmd(t_cmd *cmd, t_data *m);
void		close_all_pipes(int **fd, int n, t_data *m);
void		sigint_handler(int sig);
void		parse_here_doc(t_redir *r, t_data *m);
void		check_for_errors(t_cmd *cmd, t_data *m);
void		ft_freeptr(void *ptr);
char		*envar_here_doc(char *buff, int i);
int			valid_envar(char c);

#endif
