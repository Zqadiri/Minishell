/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 14:19:03 by iidzim            #+#    #+#             */
/*   Updated: 2021/07/14 15:16:45 by iidzim           ###   ########.fr       */
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

typedef struct s_index
{
	int	k;
	int	l;
	int	m;
}				t_index;

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


void		print_tree(t_ast *ast);

/*
** parser_utils.c
*/

t_parser	*init_parser(t_lexer *l);
void		print_msg(char *str, char *var);
int			is_redic(t_token *t);
t_token		*check_token(t_parser *p, t_ast *ast);
int			syntax_error(t_parser *p);

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

int			check_builtin(t_cmd *cmd);
void		execution(t_cmd *cmd, char **env);
int			setup_redirections(t_cmd *cmd, t_data *m);

#endif
