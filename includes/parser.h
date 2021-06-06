/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 14:19:03 by iidzim            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/06/06 21:00:08 by iidzim           ###   ########.fr       */
=======
<<<<<<< HEAD
/*   Updated: 2021/06/03 17:00:42 by zqadiri          ###   ########.fr       */
=======
/*   Updated: 2021/06/05 19:13:32 by iidzim           ###   ########.fr       */
>>>>>>> d5fbec1f4e55babfe85120b05034b7f49fc7c868
>>>>>>> da133498370b039815421eaf02ab501eeed5388e
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
	compound,
	pipe_ast,
	arg_ast
}			t_ast_type;

typedef struct s_ast
{
	t_ast_type		type;
	struct s_ast	**comp_values;
	int				comp_size;
	struct s_ast	**pipecmd_values;
	int				pipecmd_size;
	t_token			**args;
	int				args_size;
}					t_ast;

typedef struct s_zineb
{
    char    **argvs;
    t_redir *r;
}               t_zineb;

/*
** parser_utils.c
*/

t_parser	*init_parser(t_lexer *l);
int			parse_expected_token(t_parser *p, t_token_type type);
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

t_ast		*init_ast(t_ast_type type);
void		print_tree(t_ast *ast);
t_zineb		*visitor(t_ast *ast);
void		print_zineb(t_zineb *z);

/*
** free.c
*/

void		is_notempty(void *ptr);
t_ast		*free_pip_args(t_ast *ast);
t_ast		*free_tree(t_ast *ast);
void		free_parser(t_parser *p);


#endif