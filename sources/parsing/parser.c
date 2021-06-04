/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:37:40 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/04 12:08:18 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ! filename -> cmd or delim
// ! previous -> current token
// ? l->buffer = |echo ok > |
// * semicolon at the end of line -> valid


t_token	*check_token(t_parser *p, char **str)
{
	if (!syntax_error_pipe_semi(p))
		return (NULL);
	if (is_redirection(p->prev_token))
	{
		if (!parse_expected_token(p, id))
			return (NULL);
		*str = ft_strjoin(*str, p->prev_token->value);
		*str = ft_strjoin(*str, " ");
	}
	else
	{
		*str = ft_strjoin(*str, p->curr_token->value);
		*str = ft_strjoin(*str, " ");
	}
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
		*str = ft_strjoin(*str, " ");
		// printf("f:parse_args -- prev [%s][%u]\n", p->prev_token->value, p->prev_token->type);
		// printf("f:parse_args -- curr [%s][%u]\n", p->curr_token->value, p->curr_token->type);
	}
	while (p->curr_token->type != eof)
	{
		ast->args_size += 1;
		ast->args = realloc(ast->args, (ast->args_size + 1) * sizeof(t_token));
		p->prev_token = p->curr_token;
		p->curr_token = get_next_token(p->lexer);
		if (p->curr_token->type == eof)
			break ;
		ast->args[ast->args_size] = check_token(p, str);
		if (!ast->args[ast->args_size])
			return (NULL);
		if (ast->args[ast->args_size]->type == pip
			|| ast->args[ast->args_size]->type == semi)
			break;
	}
	if (!syntax_error_pipe_semi(p))
		return (NULL);
	return (ast);
}

t_ast	*parse_pipe(t_parser *p, char **str)
{
	t_ast	*ast;

	ast = init_ast(pipe_ast);
	ast->pipecmd_values = (t_ast**)malloc(sizeof(t_ast*));
	if (!ast->pipecmd_values)
		return (NULL);
	ast->pipecmd_size = 1;
	while (p->curr_token->type != eof)
	{
		ast->pipecmd_values[ast->pipecmd_size - 1] = parse_args(p, str);
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
			break;
		}
	}
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
		if (!ast->comp_values[ast->comp_size - 1])
			return (NULL);
		ast->comp_size += 1;
		ast->comp_values = realloc(ast->comp_values, ast->comp_size
			* sizeof(t_ast*));
	}
	ast->comp_size -= 1;
	// printf("----------------f:final result\tstr = [%s]\n", str);
	return (ast);
}
