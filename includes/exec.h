/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 15:03:30 by zqadiri           #+#    #+#             */
/*   Updated: 2021/06/07 10:10:45 by iidzim           ###   ########.fr       */
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

# define HISTSIZE 30000
# define HISTFILE "history.txt"

char					**g_env_var;

typedef struct s_tc_cmd
{
	char	*cmd_im; // Enter insert mode 
	char	*cmd_ic; // Insert character
	char	*cmd_ei; // end insert mode

	char	*cmd_dm; // Enter delete mode
	char	*cmd_dc; // Delete character
	char	*cmd_ed; // End delete mode
	char	*cmd_dl; // Delete line

	char	*cmd_ce; // Clear to end of line
	char	*cmd_le; // move cursor one left position

	char	*cmd_ch; // Indicates screen relative cursor motion
}				t_tc_cmd;

typedef struct s_index
{
	struct termios		*old_attr;
	struct termios		*term;
	char				*buf;
	int					cursor;
	char				**history;
	int					fd;
	int					delete_cur;
	char				*line;
	t_tc_cmd			tc_cmd;
}				t_index;

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
int		check_builtin(char **args);
int		launch(char **env, char **arg);

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

void	reset_term(struct termios *old_attr);
int		check_signals(void);
int		get_history_file(t_index *m);
void	delete_char(t_index *m);
int		get_str_cmd(t_index *m);

#endif
