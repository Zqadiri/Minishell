/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 15:03:30 by zqadiri           #+#    #+#             */
/*   Updated: 2021/05/15 17:31:22 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H

#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/*
** Function Declarations for builtin shell commands:
*/
int cd_builtin(char **);
int echo_builtin(char **);
int env_builtin(char **);
int exit_builtin(char **);
int	launch(char **env);


#endif