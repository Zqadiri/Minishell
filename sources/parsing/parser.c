/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:37:40 by iidzim            #+#    #+#             */
/*   Updated: 2021/05/25 19:04:48 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*check_token(t_parser *p)
{
	t_token *t;

	
	if (p->prev_token->type == id)
		// expect all types
	
	if (p->prev_token->type == pip)
		// expect all types except semi
	
	if (p->prev_token->type == semi)
		// expect all types except pipe
	
	// if the previous token is_redirection then the next token must be an id
	if (is_redirection(p, 'p'))
		parse_expected_token(p, id);
	t = p->curr_token;
	return (t);
}

t_ast	*parse_args(t_parser *p)
{
	t_ast	*ast;
	int		i;

	ast = init_ast(arg_ast);
	ast->args = (t_token*)malloc(sizeof(t_token));
	if (!ast->args)
		return (NULL);
	i = 0;
	while (p->curr_token->type != eof || p->curr_token != pip
		|| p->curr_token->type != semi)
	{
		ast->args_size += 1;
		//check syntax error : pipe, semicolon, redirection, id
		//get_next_token -> check err -> store the value then move to the next token 
		ast->args[i] = check_token(p);
		i++;
	}
	return (ast);
}

t_ast	*parse_cmd(t_parser *p)
{
	t_ast	*ast;
	int     i;

	ast = init_ast(cmd_ast);
	ast->simplecmd_values = (t_ast**)malloc(sizeof(t_ast*));
	if (!ast->simplecmd_values)
		return (NULL);
	i = 0;
	while (p->curr_token->type != eof)
	{
		ast->simplecmd_size += 1;
		ast->simplecmd_values[i] = parse_args(p);
		i++;
	}
	return (ast);
}

t_ast	*parse_pipe(t_parser *p)
{
	t_ast	*ast;
	int		i;

	ast = init_ast(pipe_ast);
	ast->pipecmd_values = (t_ast**)malloc(sizeof(t_ast*));
	if (!ast->pipecmd_values)
		return (NULL);
	i = 0;
	while (p->curr_token->type != eof)// && p->curr_token->type = pip)
	{
		ast->pipecmd_size += 1;
		ast->pipecmd_values[i] = parse_cmd(p);
		i++;
	}
	return (ast);
}

t_ast	*parse_compound(t_parser *p)
{
	t_ast	*ast;
	int		i;
	
	if (!p)
		return (NULL);
	ast = init_ast(compound);
	ast->comp_values = (t_ast**)malloc(sizeof(t_ast*));
	if (!ast->comp_values)
		return (NULL);
	i = 0;
	while (p->curr_token->type != eof)
	{
		ast->comp_size += 1;
		ast->comp_values[i] = parse_pipe(p);
		i++;
		//realloc
	}
	return (ast);
}
