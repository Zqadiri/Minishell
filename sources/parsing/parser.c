/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:37:40 by iidzim            #+#    #+#             */
/*   Updated: 2021/05/26 16:16:02 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_expected_token(t_parser *p, e_token_type type)
{
	if (p->curr_token->type == type)
	{
		p->prev_token = p->curr_token;
		p->curr_token = get_next_token(p->lexer);
	}
	else
	{
		printf("minishell: syntax error near unexpected token `%s'\n",
			p->prev_token->value);
		//free before exit
		exit(EXIT_FAILURE);
	}
	// else
	// {
	// 	p->prev_token->value = p->curr_token->value;
	// 	p->prev_token->type = illegal;
	// 	p->curr_token = get_next_token(p->lexer);
	// }
}

void	syntax_error_pipe_semi(t_parser *p)
{
	if ((p->prev_token->type == pip && p->curr_token->type == semi)
			|| (p->prev_token->type == semi && p->curr_token->type == pip))
		printf("minishell: syntax error near unexpected token `%s'\n",
			p->prev_token->value);
	if ((p->prev_token->type == pip && p->curr_token->type == eof)
			|| (p->prev_token->type == semi && p->curr_token->type == eof))
		printf("minishell: syntax error near unexpected token `%s'\n",
			p->prev_token->value);
	//free before exit
	exit(EXIT_FAILURE);
}

int	is_redirection(t_token *t)
{
	if (t->type == great || t->type == greater || t->type == less)
		return (1);
	return (0);
}

t_token	*check_token(t_parser *p, int i)
{
	//!skip the first token bcz the current and the previous token are the same
	if (i == 1)
		p->curr_token = get_next_token(p->lexer);
	syntax_error_pipe_semi(p);
	//? if the previous token is_redirection then the next token must be an id
	// bash-3.2$ echo ok > ; echo ok
	// bash: syntax error near unexpected token `;'
	if (is_redirection(p->prev_token))
	{
		if (p->prev_token->type == eof)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			// free before exit
			exit(EXIT_FAILURE);
		}
	}
	else
		parse_expected_token(p, id);
	if (p->prev_token->type == id)
	{
		p->prev_token = p->curr_token;
		p->curr_token = get_next_token(p->lexer);
	}
	return (p->curr_token);
}

t_ast	*parse_args(t_parser *p)
{
	t_ast	*ast;

	ast = init_ast(arg_ast);
	ast->args = (t_token*)malloc(sizeof(t_token));
	if (!ast->args)
		return (NULL);
	ast->args_size += 1;
	while (p->curr_token->type != eof)
	{
		ast->args[ast->args_size - 1] = check_token(p, ast->args_size);
		ast->args_size += 1;
		ast->args = realloc(ast->args, ast->args_size * sizeof(t_token));
		if (ast->args[ast->args_size - 1]->type == pip
			|| ast->args[ast->args_size - 1]->type == semi)
			break;
	}
	return (ast);
}

t_ast	*parse_cmd(t_parser *p)
{
	t_ast	*ast;

	ast = init_ast(cmd_ast);
	ast->simplecmd_values = (t_ast**)malloc(sizeof(t_ast*));
	if (!ast->simplecmd_values)
		return (NULL);
	ast->simplecmd_size += 1;
	while (p->curr_token->type != eof)
	{
		ast->simplecmd_values[ast->simplecmd_size - 1] = parse_args(p);
		ast->simplecmd_size += 1;
		ast->simplecmd_values = realloc(ast->comp_values, ast->simplecmd_size
			* sizeof(t_ast*));
		if (ast->args[ast->args_size - 1]->type == pip
			|| ast->args[ast->args_size - 1]->type == semi)
			break;
	}
	return (ast);
}

t_ast	*parse_pipe(t_parser *p)
{
	t_ast	*ast;

	ast = init_ast(pipe_ast);
	ast->pipecmd_values = (t_ast**)malloc(sizeof(t_ast*));
	if (!ast->pipecmd_values)
		return (NULL);
	ast->pipecmd_size += 1;
	while (p->curr_token->type != eof)
	{
		ast->pipecmd_values[ast->pipecmd_size - 1] = parse_cmd(p);
		ast->pipecmd_size += 1;
		ast->pipecmd_values = realloc(ast->comp_values, ast->pipecmd_size
			* sizeof(t_ast*));
		if (ast->args[ast->args_size - 1]->type == semi)
			break;
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
	ast->comp_size += 1;
	if (!ast->comp_values)
		return (NULL);
	while (p->curr_token->type != eof)
	{
		ast->comp_values[ast->comp_size - 1] = parse_pipe(p);
		ast->comp_size += 1;
		ast->comp_values = realloc(ast->comp_values, ast->comp_size
			* sizeof(t_ast*));
	}
	return (ast);
}
