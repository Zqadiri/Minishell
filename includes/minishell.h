/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:28:30 by iidzim            #+#    #+#             */
/*   Updated: 2021/04/11 18:21:59 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../libft/libft.h"

#define PATH_MAX 15000

typedef struct s_cmd
{
    char *cmd_line;
    char **token;
    char index;
    int flag;
    int redic;
}               t_cmd;

typedef struct s_source
{   
    char *buffer;       // the input text
    long bufsize;       // size of the input text
    long  curpos;       // absolute char position in source
}               t_source;

typedef struct s_cmdlist
{
    t_cmd cmd;
    struct s_cmdlist *next_cmd;
}               t_cmdlist; 

void print_prompt();
void read_cmd(t_source *x);
// t_cmd parser_cmd(char *cmd_line);
// void exec_cmd(t_cmd *x);


#endif
