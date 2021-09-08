/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:37:40 by iidzim            #+#    #+#             */
/*   Updated: 2021/09/08 17:55:39 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*parse_args_helper(t_parser *p)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	init_ast(ast, arg_ast);
	ast->args = (t_token **)malloc(sizeof(t_token *) * 2);
	if (!ast->args)
		return (NULL);
	ast->args[1] = NULL;
	if (ast->args_size == 0)
	{
		ast->args[0] = p->curr_token;//??
		if (p->curr_token->type == pip)
		{
			print_msg("minishell: syntax error near unexpected token 0",
				p->curr_token->value);
			free_parser2(&p);
			free_tree(ast);
			return (NULL);
		}
		ast->args_size += 1;
	}
	return (ast);
}

int	init_parse_args(t_ast *ast, t_parser *p)
{
	// t_token	*t;

	ast->args_size += 1;
	ast->args = realloc_ast_args(ast, ast->args_size);
	p->prev_token = p->curr_token;
	// t = p->curr_token;
	p->curr_token = get_next_token(p->lexer);
	// free(t->value);
	ast->args[ast->args_size - 1] = check_token(p, ast);
	if (!ast->args[ast->args_size - 1])
	{
		// free_parser2(p);
		// free(p->lexer->buffer);
		// free(p->curr_token->value);
		// free(p->curr_token);
		// free(p);
		// ?free_tree3(ast->args, ast->args_size);
		// ?free_tree(ast);
		return (0);
	}
	return (1);
}

t_ast	*parse_args(t_parser *p)
{
	t_ast		*ast;
	// t_token		*temp;

	ast = parse_args_helper(p);
	if (!ast)
		return (NULL);
	while (p->curr_token->type != eof)
	{
		if (!init_parse_args(ast, p))
		{
			free_tree(ast);
			return  (NULL);
		}
		if (ast->args[ast->args_size - 1]->type == pip)
		{
			if (p->prev_token)
			{
				printf("**5\n");
				free(p->prev_token->value);
				p->prev_token->value = NULL;
				// free(p->prev_token);
				// p->prev_token = NULL;
			}
			p->prev_token = p->curr_token;
			p->curr_token = get_next_token(p->lexer);
			// printf("prev -> <%s>, curr -> <%s>\n", p->prev_token->value, p->curr_token->value);
			break ;
		}
		if (ast->args[ast->args_size - 1]->type == eof)
			break ;
	}
	if (!syntax_error(p))
	{
		if (ast)
			free_tree(ast);	
		return (NULL);
	}
	return (ast);
}

t_ast	*parse_pipe(t_parser *p)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	init_ast(ast, pipe_ast);
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
			// printf("here\n");
			// free_parser(p);
			// free(*ast->pipecmd_values);
			// printf("here\n");
			free_tree(ast);
			return (NULL);
		}
		if (p->prev_token->type == pip)
		{
			// if(p->curr_token->type != eof)
			// {
			// 	printf("oo\n");
			// 	// free_parser(&p);
			// 	// free_tree(&ast);
			// 	// return (NULL);
			// }
			ast->pipecmd_size += 1;
			ast->pipecmd_values = realloc_ast_node(ast, ast->pipecmd_size + 1);
		}
	}
	free_parser(&p);
	return (ast);
}
