/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:28:30 by iidzim            #+#    #+#             */
/*   Updated: 2021/04/22 14:46:46 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include "../libft/libft.h"

#define PATH_MAX 15000
#define PIPE 124
#define GREAT 62
#define GREATER ">>"
#define LESS 60
#define DQUOTE 34
#define SQUOTE 39
#define SEMICOLON 59
#define SPACE 32
#define CMD "cmd"
#define PARAM "param"
#define ILLEGAL "err"
#define LITERAL "val"
#define EOF 0

typedef struct s_token
{
    char *value;
    char *type;
}               t_token;

typedef struct s_lexer
{   
    char *buffer;       // the input text
    int bufsize;       // size of the input text
    int curpos;        // absolute char position in source
    int readpos;        // after current pos
    char c;             // current char under examination
    //  + check EOF
}               t_lexer;

typedef struct s_cmdlist
{
    t_token **tokens;
    int pipe;
    struct s_cmdlist *next_cmd;
}               t_cmdlist;

void print_prompt();
void read_cmd(t_lexer *x);
// void lexer(t_cmdlist *l, t_lexer *t);
// t_cmdlist parse_cmd(t_lexer *t);
void exec_cmd();


//linkedlist
int list_size(t_cmdlist *l);
t_cmdlist *create(t_token **cmd, int pipe);
void add_back(t_cmdlist **l, t_token **cmd, int pipe);
void push(t_cmdlist **l, t_token **cmd, int pipe);
void print_cmd(t_cmdlist *l);


#endif
