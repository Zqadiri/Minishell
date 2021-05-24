/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:37:40 by iidzim            #+#    #+#             */
/*   Updated: 2021/05/24 20:15:24 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parser	*init_parser(t_lexer *l)
{
	t_parser	*p;

	if (!l)
		return (NULL);
	p = malloc(sizeof(t_parser));
	if (!p)
		return (NULL);
	p->lexer = l;
	p->curr_token = get_next_token(l);
	p->prev_token = p->curr_token;
	printf("current token value-> [%s]\n", p->curr_token->value);
	printf("current token type-> [%u]\n", p->curr_token->type);
	// printf("previous token -> [%s]\n", p->prev_token->value);
	return (p);
}

// void	parse_expected_token(t_parser *p, e_token_type type)
// {
// 	if (p->curr_token->type == type)
// 	{
// 		p->prev_token = p->curr_token;
// 		p->curr_token = get_next_token(p->lexer);
// 	}
// 	else
// 	{
// 		// printf("Unexpected token `%s', with type %d", p->curr_token->value,
// 		// 	p->curr_token->type);
// 		printf("syntax error near unexpected token %s\n", p->curr_token->value); 
// 		exit(EXIT_FAILURE);
// 	}
// }

// t_ast	*parse_id(t_parser *p)
// {
// 	t_ast	ast;
// 	t_ast	simple_cmd;
// 	char	*first_tok;

// 	parse_expected_token(p, id);
// 	first_tok = p->prev_token->value;
// 	ast = init_ast(pipe_ast);
// 	return (ast);
// }

// t_ast	*parse_redirection(t_parser *p)
// {
// 	// t_ast	*ast;
// 	// t_ast	*simple_cmd;
// 	// char	*redir;

// 	//get next token 
// 	parse_expected_token(p, id);
	
// }

// t_ast	*parse_pipeline(t_parser *p)
// {
// 	t_ast	*ast;

// 	ast = init_ast(pipe_ast);
// 	ast->pipecmd_values = (t_ast**)malloc(sizeof(t_ast*));
// 	if (!ast->pipecmd_values)
// 		return (NULL);
// 	ast->pipecmd_values[0] = parse_stat(p);
// 	ast->pipecmd_size += 1;
// 	while (p->curr_token->type != eof)
// 	{
// 		parse_expected_token(p, pip);
		
// 	}
// 	return (ast);
// }

// t_ast	*parse_stat(t_parser *p)
// {
// 	if (p->curr_token->type == semi || p->curr_token->type == pip)
// 	{
// 		p->curr_token->type = illegal;
// 		printf("Unexpected token `%s', with type %d", p->curr_token->value,
// 			p->curr_token->type);
// 		exit(EXIT_FAILURE);
// 	}
// 	if (p->curr_token->type == id)
// 		return (parse_id(p));
// 	if (p->curr_token->type == great || p->curr_token->type == greater
// 		|| p->curr_token->type == less)
// 		return (parse_redirection(p));
// 	// return ();
// }

// t_ast	*parse_statements(t_parser *p)
// {
// 	t_ast	*ast;

// 	ast = init_ast(compound);
// 	ast->comp_values = (t_ast**)malloc(sizeof(t_ast*));
// 	if (!ast->comp_values)
// 		return (NULL);
// 	ast->comp_values[0] = parse_stat(p);
// 	ast->comp_size += 1;
// 	while (p->curr_token->type != eof) // while(1)
// 	{
// 		parse_expected_token(p, semi);
// 		if (p->curr_token->type == eof)
// 			break ;
// 		ast->comp_size += 1;
// 		ast->comp_values = realloc(ast->comp_values,
// 				ast->comp_size * sizeof(t_ast*));
// 		ast->comp_values[ast->comp_size - 1] = parse_stat(p);
// 	}
// 	return (ast);
// }

// // ToDo:
// // expectPeek() : primary purpose is to enforce the correctness of the order
// // of tokens by checking the type of the next token.
