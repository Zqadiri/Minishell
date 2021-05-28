/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:28:30 by iidzim            #+#    #+#             */
/*   Updated: 2021/05/28 13:23:42 by iidzim           ###   ########.fr       */
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
#include "parser.h"

#define PATH_MAX 15000

void print_prompt();
t_lexer *read_cmd();
t_ast *init_ast(e_ast_type type);
void print_tree(t_ast *ast);


// /!\ update linked list function - new struct AST
// int list_size(t_cmdlist *l);
// t_cmdlist *create(t_token *cmd, int pipe);
// void add_back(t_cmdlist **l, t_token *cmd, int pipe);
// void push(t_cmdlist **l, t_token *cmd, int pipe);
// void print_cmd(t_cmdlist *l);


/*
** History
*/


int history(t_lexer *l);

#endif
