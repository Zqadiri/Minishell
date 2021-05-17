/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 15:03:30 by zqadiri           #+#    #+#             */
/*   Updated: 2021/05/17 09:18:19 by zqadiri          ###   ########.fr       */
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

int     cd_builtin(char **);
int     echo_builtin(char **);
int     env_builtin(char **);
int     exit_builtin(char **);
int     launch(char **env, char **arg);

/*
** Utils
*/

int     quit(void);
int		len(char **env);


#endif