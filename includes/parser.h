/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 14:19:03 by iidzim            #+#    #+#             */
/*   Updated: 2021/07/10 09:38:40 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include "lexer.h"
# include "../libft/libft.h"

typedef struct s_parser
{
	t_lexer	*lexer;
	t_token	*curr_token;
	t_token	*prev_token;
}				t_parser;

typedef struct s_redir
{
	t_token_type	type;
	char			*filename;
}					t_redir;

typedef enum e_ast_type
{
	pipe_ast,
	arg_ast
}			t_ast_type;

typedef struct s_ast
{
	t_ast_type		type;
	struct s_ast	**pipecmd_values;
	int				pipecmd_size;
	t_token			**args;
	int				redir_nbr;
	int				args_size;
}					t_ast;

typedef struct s_cmd
{
	char			**argvs;
	int				args_size;
	t_redir			*r;
	int				redir_nbr;
	t_token_type	type;
}               t_cmd;

void		print_tree(t_ast *ast);

/*
** parser_utils.c
*/

t_parser	*init_parser(t_lexer *l);
t_token		*check_token(t_parser *p, t_ast *ast);
int			parse_expected_token(t_parser *p, t_token_type type);
int			syntax_error(t_parser *p);
int			is_redic(t_token *t);

/*
** parser.c
*/

t_ast		*parse_pipe(t_parser *p);

/*
** ast.c
*/

t_ast		*init_ast(t_ast_type type);
t_cmd		*visitor(t_ast *ast);

/*
** free.c
*/

void		is_notempty(void *ptr);
void		free_tree(t_ast *ast);
void		free_tree3(t_token **token, int size);
void		free_tree2(t_ast **ast);
void		free_parser(t_parser *p);

/*
** exec
*/

void		execution (t_cmd *cmd);

#endif