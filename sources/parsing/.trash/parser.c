/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 15:18:36 by iidzim            #+#    #+#             */
/*   Updated: 2021/05/25 15:19:37 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*parse_id(t_parser *p)
{
	t_ast	*ast;
	t_ast	*simple_cmd;
	char	*first_tok;

	parse_expected_token(p, id);
	first_tok = p->prev_token->value;
	ast = init_ast(pipe_ast);
	return (ast);
}

t_ast	*parse_redirection(t_parser *p)
{
	// t_ast	*ast;
	// t_ast	*simple_cmd;
	// char	*redir;

	//get next token 
	parse_expected_token(p, id);
	
}

t_ast	*parse_pipeline(t_parser *p)
{
	t_ast	*ast;

	ast = init_ast(pipe_ast);
	ast->pipecmd_values = (t_ast**)malloc(sizeof(t_ast*));
	if (!ast->pipecmd_values)
		return (NULL);
	ast->pipecmd_values[0] = parse_stat(p);
	ast->pipecmd_size += 1;
	while (p->curr_token->type != eof)
	{
		parse_expected_token(p, pip);
		
	}
	return (ast);
}

t_ast	*parse_stat(t_parser *p)
{
	if (p->curr_token->type == semi || p->curr_token->type == pip)
	{
		p->curr_token->type = illegal;
		printf("minishell: syntax error near unexpected token %s\n",
			p->curr_token->value);
		exit(EXIT_FAILURE);
	}
	if (p->curr_token->type == id)
		return (parse_id(p));
	if (p->curr_token->type == great || p->curr_token->type == greater
		|| p->curr_token->type == less)
		return (parse_redirection(p));
	// return ();
}

t_ast	*parse_statements(t_parser *p)
{
	t_ast	*ast;

	ast = init_ast(compound);
	ast->comp_values = (t_ast**)malloc(sizeof(t_ast*));
	if (!ast->comp_values)
		return (NULL);
	ast->comp_values[0] = parse_stat(p);
	ast->comp_size += 1;
	while (p->curr_token->type != eof) // while(1)
	{
		parse_expected_token(p, semi);
		if (p->curr_token->type == eof)
			break ;
		ast->comp_size += 1;
		ast->comp_values = realloc(ast->comp_values,
				ast->comp_size * sizeof(t_ast*));
		ast->comp_values[ast->comp_size - 1] = parse_stat(p);
	}
	return (ast);
}
