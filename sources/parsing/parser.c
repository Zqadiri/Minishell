/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:37:40 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/05 18:57:08 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*check_token(t_parser *p)
{
	if (!syntax_error_pipe_semi(p))
		return (NULL);
	if (is_redirection(p->prev_token))
	{
		if (!parse_expected_token(p, id))
			return (NULL);
	}
	return (p->curr_token);
}

t_ast	*parse_args(t_parser *p)
{
	t_ast	*ast;

	ast = init_ast(arg_ast);
	ast->args = (t_token**)malloc(sizeof(t_token*));
	if (!ast->args)
		return (NULL);
	if (ast->args_size == 0)
	{
		ast->args[ast->args_size] = malloc(sizeof(t_token));
		ast->args[ast->args_size] = p->curr_token;
		if (p->curr_token->type == pip || p->curr_token->type == semi)
		{
			printf("minishell: syntax error near  unexpected token '%s'\n",
				p->curr_token->value);
			return (NULL);
		}
	}
	while (p->curr_token->type != eof)
	{
		ast->args_size += 1;
		ast->args = realloc(ast->args, (ast->args_size + 1) * sizeof(t_token));
		p->prev_token = p->curr_token;
		p->curr_token = get_next_token(p->lexer);
		ast->args[ast->args_size] = check_token(p);
		if (!ast->args[ast->args_size])
			return (NULL);
		if (ast->args[ast->args_size]->type == eof
			|| ast->args[ast->args_size]->type == pip
			|| ast->args[ast->args_size]->type == semi)
			break ;
	}
	if (!syntax_error_pipe_semi(p))
		return (NULL);
	return (ast);
}

t_ast	*parse_pipe(t_parser *p)
{
	t_ast	*ast;

	ast = init_ast(pipe_ast);
	ast->pipecmd_values = (t_ast**)malloc(sizeof(t_ast*));
	if (!ast->pipecmd_values)
		return (NULL);
	ast->pipecmd_size = 1;
	while (p->curr_token->type != eof)
	{
		ast->pipecmd_values[ast->pipecmd_size - 1] = parse_args(p);
		if (!ast->pipecmd_values[ast->pipecmd_size - 1])
			return (NULL);
		if (p->curr_token->type == pip)
		{
			ast->pipecmd_size += 1;
			ast->pipecmd_values = realloc(ast->comp_values, ast->pipecmd_size
					* sizeof(t_ast*));
		}
		if (p->curr_token->type == semi)
		{
			p->prev_token = p->curr_token;
			p->curr_token = get_next_token(p->lexer);
			break ;
		}
	}
	return (ast);
}

t_ast	*parse_compound(t_parser *p)
{
	t_ast	*ast;

	if (!p)
		return (NULL);
	ast = init_ast(compound);
	ast->comp_values = (t_ast**)malloc(sizeof(t_ast*));
	if (!ast->comp_values)
		return (NULL);
	ast->comp_size = 1;
	while (p->curr_token->type != eof)
	{
		ast->comp_values[ast->comp_size - 1] = parse_pipe(p);
		if (!ast->comp_values[ast->comp_size - 1])
			return (free_tree(ast));
		ast->comp_size += 1;
		ast->comp_values = realloc(ast->comp_values, ast->comp_size
				* sizeof(t_ast*));
	}
	ast->comp_size -= 1;
	return (ast);
}
