/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 14:19:03 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/04 17:03:18 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
#include "../libft/libft.h"

typedef struct s_parser
{
	t_lexer *lexer;
	t_token *curr_token;
	t_token *prev_token;
}				t_parser;

typedef struct		s_redir
{
	e_token_type	type;
	char			*filename;
}					t_redir; 

typedef enum t_ast_type
{
	compound,
	pipe_ast,
	arg_ast
}			e_ast_type;

typedef struct s_ast
{
	e_ast_type type;
	//AST_COMPOUND
	struct s_ast **comp_values;
	int comp_size;
	//AST_PIPE
	struct s_ast **pipecmd_values;
	int pipecmd_size;
	//AST_ARG
	t_token **args;
	// t_redir **redir;
	int args_size;
}				t_ast;

/*
** parser_utils.c
*/
t_parser	*init_parser(t_lexer *l);
int			parse_expected_token(t_parser *p, e_token_type type);
int			syntax_error_pipe_semi(t_parser *p);
int			is_redirection(t_token *t);

/*
** parser.c
*/
t_ast		*parse_compound(t_parser *p);
t_ast		*parse_pipe(t_parser *p);
t_ast		*parse_cmd(t_parser *p);
t_ast		*parse_args(t_parser *p);
t_token		*check_token(t_parser *p);

/*
** ast.c
*/
t_ast		*init_ast(e_ast_type type);
void		visitor(t_ast *ast);
t_ast		*free_tree(t_ast *ast);
#endif