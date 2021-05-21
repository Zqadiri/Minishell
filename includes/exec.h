/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 15:03:30 by zqadiri           #+#    #+#             */
/*   Updated: 2021/05/21 10:39:31 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

char					**g_env_var;

/*
** Function Declarations for builtin shell commands
*/

int     cd_builtin(char **arg);
int     echo_builtin(char **arg);
int     pwd_builtin();
int     env_builtin();
void    exit_builtin(char **);
int     unset_builtin(char **args);
int     export_builtin(char **arg);

int		dup_env_var(char **env);
char	**get_path(void);
int     launch(char **env, char **arg);

/*
** Utils
*/

int     quit(void);
int		len(char **env);
int		alpha(char *key);

/*
** Helpers 
*/

int     find_env(char *key);
char    *get_env_var_by_key(char *key);
char	*return_value(const char *s, int c);
int		check_builtin(char **args);


#endif