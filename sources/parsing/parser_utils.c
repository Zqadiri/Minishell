/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 11:52:47 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/02 18:32:57 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parser	*init_parser(t_lexer *l)
{
		
	t_parser	*p;

	if (!l)
		return (NULL);
	p = malloc(sizeof(t_parser));
	if (!p)
		return (NULL);
	p->lexer = l;
	p->curr_token = get_next_token(l);
	p->prev_token = p->curr_token;
	if (p->curr_token->type == pip || p->curr_token->type == semi)
	{
		printf("minishell: syntax error near unexpected token '%s'\n",
			p->curr_token->value);
		// free before exit
		return (NULL);
	}
	// printf("current token value-> [%s]\n", p->curr_token->value);
	// printf("current token type-> [%u]\n", p->curr_token->type);
	// printf("previous token -> [%s]\n", p->prev_token->value);
	//free p
	return (p);
}


/*
** expected_token() : primary purpose is to enforce the correctness of
** the order of tokens by checking the type of the next token.
*/

int	parse_expected_token(t_parser *p, e_token_type type)
{
	printf("f:parse_expected_token\tcurr before = [%s]\n", p->curr_token->value);
	if (p->curr_token->type == type)
	{
		p->prev_token = p->curr_token;
		p->curr_token = get_next_token(p->lexer);
	// 	printf("f:parse_expected_token\tprev = [%s]\n", p->prev_token->value);
	// 	printf("f:parse_expected_token\tcurr = [%s]\n", p->curr_token->value);
	}
	else
	{
		printf("minishell: syntax error near unexpected token `%s'\n",
			p->curr_token->value);
		//free before exit
		// exit(EXIT_FAILURE);
		return (0);
	}
	return (1);
	// else
	// {
	// 	p->prev_token->value = p->curr_token->value;
	// 	p->prev_token->type = illegal;
	// 	p->curr_token = get_next_token(p->lexer);
	// }
}

int	syntax_error_pipe_semi(t_parser *p)
{
	// printf("f:syntax_error\t prev [%s] -- curr [%s]\n", p->prev_token->value, p->curr_token->value);
	if ((p->prev_token->type == pip && p->curr_token->type == semi)
			|| (p->prev_token->type == semi && p->curr_token->type == semi)
			|| (p->prev_token->type == pip && p->curr_token->type == pip)
			|| (p->prev_token->type == semi && p->curr_token->type == pip))
	{
		printf("minishell: syntax error near unexpected token `%s'\n",
			p->prev_token->value);
		// exit(EXIT_FAILURE);
		return (0);
	}
	if (p->prev_token->type == pip && p->curr_token->type == eof)
	{
		printf("minishell: syntax error near unexpected token `%s'\n",
			p->prev_token->value);
		// exit(EXIT_FAILURE);
		return (0);
	}
	if (is_redirection(p->prev_token) && p->curr_token->type == eof)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		// free before exit
		// exit(EXIT_FAILURE);
		return (0);
	}
	return (1);
	// printf("f:syntax_error_pipe_semi\tNO SYNTAX ERROR\n");
	//free before exit
	// exit(EXIT_FAILURE);
	// return ;
}

// void	syntax_error_pipe_semi(t_parser *p)
// {
// 	// printf("f:syntax_error\t prev [%s] -- curr [%s]\n", p->prev_token->value, p->curr_token->value);
// 	if ((p->prev_token->type == pip && p->curr_token->type == semi)
// 			|| (p->prev_token->type == semi && p->curr_token->type == pip))
// 		printf("minishell: syntax error near unexpected token `%s'\n",
// 			p->prev_token->value);
// 	if (p->prev_token->type == pip && p->curr_token->type == eof)
// 		printf("minishell: syntax error near unexpected token `%s'\n",
// 			p->prev_token->value);
// 	if (is_redirection(p->prev_token) && p->curr_token->type == eof)
// 		printf("minishell: syntax error near unexpected token `newline'\n");
// 	//free before exit
// 	exit(EXIT_FAILURE);
// 	// return ;
// }

int	is_redirection(t_token *t)
{
	if (t->type == great || t->type == greater || t->type == less)
		return (1);
	return (0);
}
