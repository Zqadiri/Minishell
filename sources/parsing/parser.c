/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:37:40 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/08 19:13:44 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*check_token(t_parser *p, t_ast *ast)
{
	if (!syntax_error_pipe_semi(p))
		return (NULL);
	if (is_redirection(p->prev_token))
	{
		if (!parse_expected_token(p, id))
			return (NULL);
		ast->redir_nbr += 1;
	}
	return (p->curr_token);
}

t_ast	*parse_args(t_parser *p)
{
	t_ast	*ast;

	ast = init_ast(arg_ast);
	ast->args = (t_token**)malloc(sizeof(t_token*) * 2);
	if (!ast->args)
		return (NULL);
	ast->args[1] = NULL;
	if (ast->args_size == 0)
	{
		ast->args[0] = malloc(sizeof(t_token));
		ast->args[0] = p->curr_token;
		if (p->curr_token->type == pip || p->curr_token->type == semi)
		{
			printf("minishell: syntax error near unexpected token 0`%s'\n",
				p->curr_token->value);
			return (NULL);
		}
		ast->args_size += 1;
	}
	while (p->curr_token->type != eof)
	{
		ast->args_size += 1;
		ast->args = realloc_ast_args(ast, ast->args_size + 1);
		p->prev_token = p->curr_token;
		p->curr_token = get_next_token(p->lexer);
		ast->args[ast->args_size - 1] = check_token(p, ast);
		if (!ast->args[ast->args_size - 1])
			return (NULL);
		if (ast->args[ast->args_size - 1]->type == pip
			|| ast->args[ast->args_size - 1]->type == semi)
		{
			p->prev_token = p->curr_token;
			p->curr_token = get_next_token(p->lexer);
			break ;
		}
		if (ast->args[ast->args_size - 1]->type == eof)
			break;
	}
	if (!syntax_error_pipe_semi(p))
		return (NULL);
	return (ast);
}

// t_ast	*parse_args(t_parser *p)
// {
// 	t_ast	*ast;
// 	ast = init_ast(arg_ast);
// 	ast->args = (t_token**)malloc(sizeof(t_token*));
// 	if (!ast->args)
// 		return (NULL);
// 	if (ast->args_size == 0)
// 	{
// 		ast->args[ast->args_size] = malloc(sizeof(t_token));
// 		ast->args[ast->args_size] = p->curr_token;
// 		if (p->curr_token->type == pip || p->curr_token->type == semi)
// 		{
// 			printf("minishell: syntax error near unexpected token 0`%s'\n",
// 				p->curr_token->value);
// 			return (NULL);
// 		}
// 	}
// 	while (p->curr_token->type != eof)
// 	{
// 		ast->args_size += 1;
// 		ast->args = realloc(ast->args, (ast->args_size + 1) * sizeof(t_token));
// 		p->prev_token = p->curr_token;
// 		p->curr_token = get_next_token(p->lexer);
// 		ast->args[ast->args_size] = check_token(p, ast);
// 		if (!ast->args[ast->args_size])
// 			return (NULL);
// 		if (ast->args[ast->args_size]->type == eof
// 			|| ast->args[ast->args_size]->type == pip
// 			|| ast->args[ast->args_size]->type == semi)
// 			break ;
// 	}
// 	if (!syntax_error_pipe_semi(p))
// 		return (NULL);
// 	return (ast);
// }

t_ast	*parse_pipe(t_parser *p)
{
	t_ast	*ast;

	ast = init_ast(pipe_ast);
	ast->pipecmd_values = (t_ast**)malloc(sizeof(t_ast*) * 2);
	if (!ast->pipecmd_values)
		return (NULL);
	ast->pipecmd_size = 1;
	ast->pipecmd_values[ast->pipecmd_size] = NULL;
	while (p->curr_token->type != eof)
	{
		ast->pipecmd_values[ast->pipecmd_size - 1] = parse_args(p);
		if (!ast->pipecmd_values[ast->pipecmd_size - 1])
			return (NULL);
		if (p->prev_token->type == pip)
		{
			ast->pipecmd_size += 1;
			ast->pipecmd_values = realloc_ast_node(ast, ast->pipecmd_size + 1);
		}
		if (p->prev_token->type == semi)
			break ;
	}
	return (ast);
}

t_ast	*parse_compound(t_parser *p)
{
	t_ast	*ast;

	if (!p)
		return (NULL);
	ast = init_ast(compound);
	ast->comp_values = (t_ast**)malloc(sizeof(t_ast*) * 2);
	if (!ast->comp_values)
		return (NULL);
	ast->comp_size = 1;
	ast->comp_values[ast->comp_size] = NULL;
	while (p->curr_token->type != eof)
	{
		ast->comp_values[ast->comp_size - 1] = parse_pipe(p);
		if (!ast->comp_values[ast->comp_size - 1])
			return (free_tree(ast));
		ast->comp_size += 1;
		// ast->comp_values = realloc(ast->comp_values, ast->comp_size
		// 		* sizeof(t_ast*));
		ast->comp_values = realloc_ast_node(ast, ast->comp_size + 1);
		printf("size >> [%d]\n", ast->comp_size);
	}
	ast->comp_size -= 1;
	return (ast);
}

t_ast	**realloc_ast_node(t_ast *ast, int size)
{
	t_ast	**new;
	int		i;

	if (ast->type == compound)
	{
		new = (t_ast**)malloc(sizeof(t_ast*) * size);
		i = 0;
		while (ast->comp_values[i])
		{
			new[i] = ast->comp_values[i];
			i++;
		}
		new[++i] = NULL;
		ast->comp_values = NULL;
		// free_tree(ast->comp_values);
		return (new);
	}
	else //if (ast->type == pipe_ast)
	{
		new = (t_ast**)malloc(sizeof(t_ast*) * size);
		i = 0;
		while (ast->pipecmd_values[i])
		{
			new[i] = ast->pipecmd_values[i];
			i++;
		}
		new[++i] = NULL;
		ast->pipecmd_values = NULL;
		// free_tree(ast->pipecmd_values);
		return (new);
	}
	return (NULL);
}

t_token	**realloc_ast_args(t_ast *ast, int size)
{
	t_token **new;
	int i;

	if (ast->type == arg_ast)
	{
		new = (t_token**)malloc(sizeof(t_token*) * size);
		i = 0;
		while (ast->args[i])
		{
			new[i] = ast->args[i];
			i++;
		}
		new[++i] = NULL;
		ast->args = NULL;
		// free_tree(ast->pipecmd_values);
		return (new);
	}
	return (NULL);
}
