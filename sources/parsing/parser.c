/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:37:40 by iidzim            #+#    #+#             */
/*   Updated: 2021/05/27 21:57:26 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*check_token(t_parser *p, int i)
{
	// printf("****************f:check_token\thi bitch\n");
	//!skip the first token bcz the current and the previous token are the same
	if (i == 1)
	{
		p->curr_token = get_next_token(p->lexer);
		if (p->curr_token->type == eof)
			return (p->curr_token);
		// printf("next token value-> [%s]\n", p->curr_token->value);
		// printf("next token type-> [%u]\n", p->curr_token->type);
	}
	syntax_error_pipe_semi(p);
	//? if the previous token is_redirection then the next token must be an id
	//* bash-3.2$ echo ok > ; echo ok
	//* bash: syntax error near unexpected token `;'
	if (is_redirection(p->prev_token))
	{
		if (p->prev_token->type == eof)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			// free before exit
			exit(EXIT_FAILURE);
		}
		else
			parse_expected_token(p, id);
	}
	// if (p->prev_token->type == id)
	// {
	// 	p->prev_token = p->curr_token;
	// 	p->curr_token = get_next_token(p->lexer);
	// }
	// printf("f:check_token\t<%s - %u>\n", p->curr_token->value, p->curr_token->type);
	return (p->curr_token);
}

// !infinite loop
t_ast	*parse_args(t_parser *p)
{
	t_ast	*ast;

	ast = init_ast(arg_ast);
	ast->args = (t_token**)malloc(sizeof(t_token*));
	if (!ast->args)
		return (NULL);
	ast->args[ast->args_size] = malloc(sizeof(t_token));
	ast->args[ast->args_size] = p->curr_token;
    printf("f:parse_args\tcurrent token [%s]\n", ast->args[ast->args_size]->value);
	while (p->curr_token->type != eof)
	{
		ast->args_size += 1;
		// printf("f:parse_args\tsize = %d\n", ast->args_size);
		ast->args = realloc(ast->args, (ast->args_size + 1) * sizeof(t_token));
		ast->args[ast->args_size] = check_token(p, ast->args_size);
		// printf("f:parse_args\tsize = %d\n", ast->args_size);
		break ;
		// printf("f:parse_args\thi bitch4\n");
		// printf("******f:parse_args\t[%u]\n", ast->args[ast->args_size - 1]->type);
		if (ast->args[ast->args_size - 1]->type == pip
			|| ast->args[ast->args_size - 1]->type == semi)
			break;
	}
	return (ast);
}

// t_ast	*parse_args(t_parser *p)
// {
// 	t_ast	*ast;

// 	ast = init_ast(arg_ast);
// 	ast->args = (t_token**)malloc(sizeof(t_token*));
// 	if (!ast->args)
// 		return (NULL);
// 	ast->args_size += 1;
// 	while (p->curr_token->type != eof)
// 	{
// 		printf("f:parse_args\tsize = %d\n", ast->args_size);
// 		ast->args = realloc(ast->args, (ast->args_size + 1) * sizeof(t_token));
// 		ast->args[ast->args_size] = check_token(p, ast->args_size);
// 		printf("f:parse_args\thi bitch4\n");
// 		// printf("******f:parse_args\t[%u]\n", ast->args[ast->args_size - 1]->type);
// 		if (ast->args[ast->args_size - 1]->type == pip
// 			|| ast->args[ast->args_size - 1]->type == semi)
// 			break;
// 		ast->args_size += 1;
// 	}
// 	return (ast);
// }

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
		printf("f:parse_cmd\thi bitch3\n");
		ast->simplecmd_size += 1;
		ast->simplecmd_values = realloc(ast->comp_values, ast->simplecmd_size
			* sizeof(t_ast*));
		// printf("f:parse_args\tsize = %d\n", ast->args_size);
		
		if (p->curr_token->type == pip || p->curr_token->type == semi)
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
		printf("f:parse_pipe\thi bitch2\n");
		ast->pipecmd_size += 1;
		ast->pipecmd_values = realloc(ast->comp_values, ast->pipecmd_size
			* sizeof(t_ast*));
		if (p->curr_token->type == semi)
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
		printf("f:parse_compound\thi bitch1\n");
		ast->comp_size += 1;
        printf("f:parse_compound\tsize = %d\n", ast->comp_size);
		ast->comp_values = realloc(ast->comp_values, ast->comp_size
			* sizeof(t_ast*));
	}
	return (ast);
}
