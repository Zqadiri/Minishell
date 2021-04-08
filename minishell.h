/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:28:30 by iidzim            #+#    #+#             */
/*   Updated: 2021/04/08 14:34:23 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHEKK_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_cmd
{
    char **token;
    char index;
}               t_cmd;

void print_prompt();
char *read_cmd();
t_cmd parser_cmd(char *cmd_line);
void exec_cmd(t_cmd *x);

#endif