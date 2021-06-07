/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 14:19:03 by iidzim            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/06/07 21:03:16 by iidzim           ###   ########.fr       */
=======
/*   Updated: 2021/06/07 13:51:13 by zqadiri          ###   ########.fr       */
>>>>>>> 417683395469d2617952ec50395cbcd41216d60e
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
	int				redir_nbr;
	int				args_size;
}					t_ast;

typedef struct s_cmd
{
	char			**argvs;
	t_redir			*r;
	t_token_type	type;
}               t_cmd;

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
t_ast		*parse_args(t_parser *p);
t_token		*check_token(t_parser *p, t_ast *ast);

/*
** ast.c
*/

t_ast		*init_ast(t_ast_type type);
void		print_tree(t_ast *ast);
t_cmd		*visitor(t_ast *ast);
void		print_cmd(t_cmd *z);

/*
** free.c
*/

void		is_notempty(void *ptr);
t_ast		*free_args(t_ast *ast);
t_ast		*free_tree(t_ast *ast);
void		free_parser(t_parser *p);

#endif