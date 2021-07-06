/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:37:40 by iidzim            #+#    #+#             */
/*   Updated: 2021/07/06 09:20:44 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	**realloc_ast_node(t_ast *ast, int size)
{
	t_ast	**new;
	int		i;

	if (ast->type == pipe_ast)
	{
		new = (t_ast **)malloc(sizeof(t_ast *) * size);
		i = -1;
		while (++i < ast->pipecmd_size)
			new[i] = ast->pipecmd_values[i];
		new[i] = NULL;
		ast->pipecmd_values = NULL;
		// free_tree2(ast->pipecmd_values);
		return (new);
	}
	return (NULL);
}

t_token	**realloc_ast_args(t_ast *ast, int size)
{
	t_token	**new;
	int		i;

	if (ast->type == arg_ast)
	{
		new = (t_token **)malloc(sizeof(t_token *) * size);
		i = -1;
		while (++i < ast->args_size)
			new[i] = ast->args[i];
		new[i] = NULL;
		ast->args = NULL;
		// free_tree3(ast->args, ast->args_size);
		return (new);
	}
	return (NULL);
}

t_ast	*parse_args_helper(t_parser *p)
{
	t_ast	*ast;

	ast = init_ast(arg_ast);
	ast->args = (t_token **)malloc(sizeof(t_token *) * 2);
	if (!ast->args)
		return (NULL);
	ast->args[1] = NULL;
	if (ast->args_size == 0)
	{
		ast->args[0] = malloc(sizeof(t_token));
		ast->args[0] = p->curr_token;
		if (p->curr_token->type == pip)
		{
			printf("minishell: syntax error near unexpected token 0`%s'\n",
				p->curr_token->value);
			return (NULL);
		}
		ast->args_size += 1;
	}
	return (ast);
}

t_ast	*parse_args(t_parser *p)
{
	t_ast	*ast;

	ast = parse_args_helper(p);
	if (!ast)
		return (NULL);
	while (p->curr_token->type != eof)
	{
		ast->args_size += 1;
		ast->args = realloc_ast_args(ast, ast->args_size + 1);
		p->prev_token = p->curr_token;
		p->curr_token = get_next_token(p->lexer);
		ast->args[ast->args_size - 1] = check_token(p, ast);
		if (!ast->args[ast->args_size - 1])
			return (NULL);
		if (ast->args[ast->args_size - 1]->type == pip)
		{
			p->prev_token = p->curr_token;
			p->curr_token = get_next_token(p->lexer);
			break ;
		}
		if (ast->args[ast->args_size - 1]->type == eof)
			break ;
	}
	if (!syntax_error_pipe(p))
		return (NULL);
	return (ast);
}

t_ast	*parse_pipe(t_parser *p)
{
	t_ast	*ast;

	ast = init_ast(pipe_ast);
	ast->pipecmd_values = (t_ast **)malloc(sizeof(t_ast *) * 2);
	if (!ast->pipecmd_values)
		return (NULL);
	ast->pipecmd_size = 1;
	ast->pipecmd_values[ast->pipecmd_size] = NULL;
	while (p->curr_token->type != eof)
	{
		ast->pipecmd_values[ast->pipecmd_size - 1] = parse_args(p);
		if (!ast->pipecmd_values[ast->pipecmd_size - 1])
		{
			free_tree(ast);
			return (NULL);
		}
		if (p->prev_token->type == pip)
		{
			ast->pipecmd_size += 1;
			ast->pipecmd_values = realloc_ast_node(ast, ast->pipecmd_size + 1);
		}
	}
	return (ast);
}
