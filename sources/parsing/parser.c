/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:37:40 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/02 21:55:01 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*check_token(t_parser *p, char **str)
{
	// //!skip the first token bcz the current and the previous token are the same
	// //? if the previous token is_redirection then the next token must be an id
	// //* bash-3.2$ echo ok > ; echo ok
	// //* bash: syntax error near unexpected token `;'
	printf("\n******f:check_token\t previous token [%s][%u]\n", p->prev_token->value, p->prev_token->type);
	printf("******f:check_token\t current token [%s][%u]\n", p->curr_token->value, p->curr_token->type);
	printf("**************************f:check_token\n\n");
	if (!syntax_error_pipe_semi(p))
		return (NULL);
	if (is_redirection(p->prev_token))
	{
		if (!parse_expected_token(p, id))
			return (NULL);
		*str = ft_strjoin(*str, p->prev_token->value);
		*str = ft_strjoin(*str, " ");
		printf("\n\nf:check_token\t join token -> [%s]\n\n", p->curr_token->value);
	}
	else
	{
		*str = ft_strjoin(*str, p->curr_token->value);
		*str = ft_strjoin(*str, " ");
	}
	// printf("----------------f:final result\tstr = [%s]\n", *str);
	printf(">>>>>>>>>>>out\n");
	return (p->curr_token);
}

t_ast	*parse_args(t_parser *p, char **str)
{
	t_ast	*ast;

	ast = init_ast(arg_ast);
	ast->args = (t_token**)malloc(sizeof(t_token*));
	if (!ast->args)
		return (NULL);
	// store the first token
	if (ast->args_size == 0)
	{
		ast->args[ast->args_size] = malloc(sizeof(t_token));
		ast->args[ast->args_size] = p->curr_token;
		*str = ft_strjoin(*str, p->curr_token->value);
		*str = ft_strjoin(*str, " ");
		printf("f:parse_args\t curr[%s][%u]\n", ast->args[ast->args_size]->value, ast->args[ast->args_size]->type);
	}
	while (p->curr_token->type != eof)
	{
		ast->args_size += 1;
		ast->args = realloc(ast->args, (ast->args_size + 1) * sizeof(t_token));
		printf("f:parse_arg\tcurr>>>[%s]\n", p->curr_token->value);
		p->prev_token = p->curr_token;
		p->curr_token = get_next_token(p->lexer);
		printf("f:parse_arg\tcurr****>>>[%s]\n", p->curr_token->value);
		if (p->curr_token->type == eof)
			break ;
		if (!check_token(p, str))
			return (NULL);
		ast->args[ast->args_size] = check_token(p, str);
		// printf("f:parse_arg\t current_token = [%s][%u]\n", p->curr_token->value, p->curr_token->type);
		// printf("f:parse_arg\t previous_token = [%s][%u]\n", p->prev_token->value, p->prev_token->type);

		// if (p->curr_token->type == pip || p->curr_token->type == semi)
		// 	break;
		// printf("f:parse_arg\t current_token = [%s][%u]\n", ast->args[ast->args_size - 1]->value, ast->args[ast->args_size - 1]->type);
		// printf("f:parse_arg\t ast->size token = [%s][%u]\n", ast->args[ast->args_size]->value, ast->args[ast->args_size]->type);
		if (ast->args[ast->args_size - 1]->type == pip
			|| ast->args[ast->args_size - 1]->type == semi)
			break;
	}
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	if (!syntax_error_pipe_semi(p))
		return (NULL);
	printf("f:parse_args\t before abort line [%s][%u]\n", ast->args[ast->args_size - 1]->value, ast->args[ast->args_size - 1]->type);
	printf("f:parse_args\tsize before abort [%d]\n", ast->args_size);
	if (ast->args[ast->args_size]->type == pip)
		printf("\n=========================================================pipe\n");
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
	ast->pipecmd_size = 1;
	while (p->curr_token->type != eof)
	{
		if (!parse_args(p, str))
			return (NULL);
		ast->pipecmd_values[ast->pipecmd_size - 1] = parse_args(p, str);
		printf("\t\tf:parse_pipe\t cuurent token = [%s][%u]\n", p->curr_token->value, p->curr_token->type);
		if (p->curr_token->type == pip)
		{
			ast->pipecmd_size += 1;
			ast->pipecmd_values = realloc(ast->comp_values, ast->pipecmd_size
				* sizeof(t_ast*));
		}
		// printf("++++++++++f:parse_pipe\tsize = %d\n", ast->pipecmd_size);
		if (p->curr_token->type == semi)
			break;
	}
	printf("\n=========================================================semi\n");
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
		if (!parse_pipe(p, &str))
			return (NULL);
		ast->comp_values[ast->comp_size - 1] = parse_pipe(p, &str);
		ast->comp_size += 1;
		ast->comp_values = realloc(ast->comp_values, ast->comp_size
			* sizeof(t_ast*));
		// printf("++++++++++f:parse_compound\tsize compound = [%d]\n", ast->comp_size);
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
 