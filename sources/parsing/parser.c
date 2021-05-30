/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:37:40 by iidzim            #+#    #+#             */
/*   Updated: 2021/05/30 19:49:04 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// // !infinite loop
// t_ast	*parse_args(t_parser *p, char **str)
// {
// 	t_ast	*ast;

// 	ast = init_ast(arg_ast);
// 	ast->args = (t_token**)malloc(sizeof(t_token*));
// 	if (!ast->args)
// 		return (NULL);
// 	ast->args[ast->args_size] = malloc(sizeof(t_token));
// 	ast->args[ast->args_size] = p->curr_token;
// 	ast->args_size = 1;
// 	while (p->curr_token->type != eof)
// 	{
// 		ast->args = realloc(ast->args, (ast->args_size + 1) * sizeof(t_token));
// 		p->prev_token = p->curr_token;
// 		if (ast->args_size == 1)
// 		{
// 			p->curr_token = get_next_token(p->lexer);
// 			if (p->curr_token->type == eof)
// 				break ;
// 		}
// 		ast->args[ast->args_size] = check_token(p, str);
// 		ast->args_size += 1;
// 		break ;
// 		// if (ast->args[ast->args_size - 1]->type == pip
// 		// 	|| ast->args[ast->args_size - 1]->type == semi)
// 		// 	break;
// 	}
// 	syntax_error_pipe_semi(p);
// 	// ast->args_size -= 1;
//     printf("-------->f:parse_args\tsize = %d\n", ast->args_size);
// 	return (ast);
// }

// t_ast	*parse_cmd(t_parser *p, char **str)
// {
// 	t_ast	*ast;

// 	ast = init_ast(cmd_ast);
// 	ast->simplecmd_values = (t_ast**)malloc(sizeof(t_ast*));
// 	if (!ast->simplecmd_values)
// 		return (NULL);
// 	ast->simplecmd_size += 1;
// 	while (p->curr_token->type != eof)
// 	{
// 		ast->simplecmd_values[ast->simplecmd_size - 1] = parse_args(p, str);
// 		ast->simplecmd_size += 1;
//     	// printf("-------->f:parse_cmd\tsize = %d\n", ast->simplecmd_size);
// 		ast->simplecmd_values = realloc(ast->comp_values, ast->simplecmd_size
// 			* sizeof(t_ast*));
// 		// printf("f:parse_args\tsize = %d\n", ast->args_size);
// 		printf("f:parse_cmd\t current token [%s][%u]\n", p->curr_token->value, p->curr_token->type);
// 		if (p->curr_token->type == pip || p->curr_token->type == semi)
// 		{
// 			printf("\\\\\\\\f:check_token\t previous token [%s]\n", p->prev_token->value);
// 			printf("\\\\\\\\f:check_token\t current token [%s]\n", p->curr_token->value);
// 			printf("\\\\\\\\\\\\\f:check_token\n");
// 			break;
// 		}
// 	}
// 	ast->simplecmd_size -= 1;
//     printf("-------->f:parse_cmd\tsize = %d\n", ast->simplecmd_size);
// 	return (ast);
// }

t_token	*check_token(t_parser *p, char **str)
{
	// //!skip the first token bcz the current and the previous token are the same
	// //? if the previous token is_redirection then the next token must be an id
	// //* bash-3.2$ echo ok > ; echo ok
	// //* bash: syntax error near unexpected token `;'
	// printf("******f:check_token\t previous token [%s][%u]\n", p->prev_token->value, p->prev_token->type);
	// printf("******f:check_token\t current token [%s][%u]\n", p->curr_token->value, p->curr_token->type);
	// printf("**************************f:check_token\n");
	syntax_error_pipe_semi(p);
	if (is_redirection(p->prev_token))
		parse_expected_token(p, id);
	*str = ft_strjoin(*str, p->curr_token->value);
	// printf("----------------f:final result\tstr = [%s]\n", *str);
	return (p->curr_token);
}

t_ast	*parse_args(t_parser *p, char **str)
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
		*str = ft_strjoin(*str, p->curr_token->value);
	}
	// ast->args_size += 1;
	while (p->curr_token->type != eof)
	{
		ast->args_size += 1;
		ast->args = realloc(ast->args, (ast->args_size + 1) * sizeof(t_token));
		p->prev_token = p->curr_token;
		p->curr_token = get_next_token(p->lexer);
		if (p->curr_token->type == eof)
			break ;
		ast->args[ast->args_size] = check_token(p, str);
		// ast->args_size += 1;
		if (ast->args[ast->args_size - 1]->type == pip
			|| ast->args[ast->args_size - 1]->type == semi)
			break;
	}
	syntax_error_pipe_semi(p);
	// ast->args_size -= 1;
    printf("-------->f:parse_args\tsize = %d\n", ast->args_size);
	return (ast);
}

t_ast	*parse_pipe(t_parser *p, char **str)
{
	t_ast	*ast;

	ast = init_ast(pipe_ast);
	ast->pipecmd_values = (t_ast**)malloc(sizeof(t_ast*));
	if (!ast->pipecmd_values)
		return (NULL);
	ast->pipecmd_size += 1;
	while (p->curr_token->type != eof)
	{
		// ast->pipecmd_values[ast->pipecmd_size - 1] = parse_cmd(p, str);
		ast->pipecmd_values[ast->pipecmd_size - 1] = parse_args(p, str);
		ast->pipecmd_size += 1;
		ast->pipecmd_values = realloc(ast->comp_values, ast->pipecmd_size
			* sizeof(t_ast*));	
		if (p->curr_token->type == semi)
			break;
	}
	ast->pipecmd_size -= 1;
    printf("-------->f:parse_pipe\tsize = %d\n", ast->pipecmd_size);
	return (ast);
}

t_ast	*parse_compound(t_parser *p)
{
	t_ast	*ast;
	char	*str;

	str =ft_strdup("");
	if (!p)
		return (NULL);
	ast = init_ast(compound);
	ast->comp_values = (t_ast**)malloc(sizeof(t_ast*));
	if (!ast->comp_values)
		return (NULL);
	ast->comp_size = 1;
	while (p->curr_token->type != eof)
	{
		ast->comp_values[ast->comp_size - 1] = parse_pipe(p, &str);
		ast->comp_size += 1;
		ast->comp_values = realloc(ast->comp_values, ast->comp_size
			* sizeof(t_ast*));
	}
	ast->comp_size -= 1;
    printf("-------->f:parse_compound\tsize = %d\n", ast->comp_size);

	// printf("previous token type-> [%s][%u]\n", p->prev_token->value, p->prev_token->type);
	// printf("current token value-> [%s][%u]\n", p->curr_token->value, p->curr_token->type);

	printf("----------------f:final result\tstr = [%s]\n", str);
	return (ast);
}

// ! filename -> cmd or delim
// ! previous -> current token
// ? l->buffer = |echo ok > |
// * semicolon at the end of line -> valid
 