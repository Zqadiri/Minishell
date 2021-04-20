/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:28:30 by iidzim            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/04/19 16:28:35 by iidzim           ###   ########.fr       */
=======
/*   Updated: 2021/04/12 10:57:36 by zqadiri          ###   ########.fr       */
>>>>>>> 06630d4966de4870c6a577eaf15c743bbf6899f7
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
#define PITPE 124
#define GREAT 62
#define GREATER
#define LESS 60
#define DQUOTE 34
#define SQUOTE 39
#define SEMICOLON 59
#define SPACE 32
#define CMD "cmd"
#define PARAM "param"

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
    // char c;             // current character
    //  + check EOF
}               t_lexer;

typedef struct s_cmdlist
{
    t_token **tokens;
    int pipe;
    struct s_cmdlist *next_cmd;
}               t_cmdlist;

<<<<<<< HEAD
void print_prompt();
void read_cmd(t_lexer *x);
void lexer(t_cmdlist *l, t_lexer *t);
// t_cmdlist parse_cmd(t_lexer *t);
void exec_cmd();


//linkedlist
int list_size(t_cmdlist *l);
t_cmdlist *create(t_token **cmd, int pipe);
void add_back(t_cmdlist **l, t_token **cmd, int pipe);
void push(t_cmdlist **l, t_token **cmd, int pipe);
void print_cmd(t_cmdlist *l);


=======




void        print_prompt();
void        read_cmd(t_source *x);
t_cmdlist   parse_cmd(t_source *t);
void        exec_cmd();

>>>>>>> 06630d4966de4870c6a577eaf15c743bbf6899f7
#endif
