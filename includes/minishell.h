/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:28:30 by iidzim            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/05/22 15:41:19 by iidzim           ###   ########.fr       */
=======
/*   Updated: 2021/05/22 13:31:57 by zqadiri          ###   ########.fr       */
>>>>>>> 86b5ef1e319f597ded4c409a9cdcb485e9621743
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "./exec.h"
#include "lexer.h"

#define PATH_MAX 15000

// typedef struct s_lexer
// {   
// 	char *buffer;       // the input text
// 	int bufsize;        // size of the input text
// 	int curpos;         // absolute char position in source
// 	int readpos;        // after current pos
// 	char c;             // current char under examination
// }               t_lexer;

// typedef struct s_token
// {
// 	char *value;
// 	e_token_type type;
// }               t_token;

typedef enum t_ast_type
{
	compound,
	pipe_ast,
	cmd_ast,
	arg_ast
}			e_ast_type;

typedef struct s_parser
{
	t_lexer *lexer;
	t_token *curr_token;
	t_token *prev_token;
}				t_parser;

// typedef struct s_cmdlist
// {
// 	t_token *tokens;
// 	int pipe;
// 	struct s_cmdlist *next_cmd;
// }               t_cmdlist;

typedef struct s_ast
{
	e_ast_type type;
	//AST_COMPOUND
	struct s_ast **comp_values;
	int comp_size;
	//AST_PIPE
	struct s_ast **pipecmd_values;
	int pipecmd_size;
	//AST_CMD
	struct s_ast **simplecmd_values;
	int simplecmd_size;
	//AST_ARG
	struct s_ast **args;
	int args_size;
}				t_ast;

void print_prompt();
t_ast *init_ast(e_ast_type type);
t_parser	*init_parser(t_lexer *l);


// /!\ update linked list function - new struct AST
// int list_size(t_cmdlist *l);
// t_cmdlist *create(t_token *cmd, int pipe);
// void add_back(t_cmdlist **l, t_token *cmd, int pipe);
// void push(t_cmdlist **l, t_token *cmd, int pipe);
// void print_cmd(t_cmdlist *l);





#endif
