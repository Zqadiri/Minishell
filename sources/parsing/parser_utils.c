/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 11:52:47 by iidzim            #+#    #+#             */
/*   Updated: 2021/05/25 19:03:33 by iidzim           ###   ########.fr       */
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
		return (NULL);
	}
	printf("current token value-> [%s]\n", p->curr_token->value);
	printf("current token type-> [%u]\n", p->curr_token->type);
	// printf("previous token -> [%s]\n", p->prev_token->value);
	//free p
	return (p);
}


/*
** expected_token() : primary purpose is to enforce the correctness of
** the order of tokens by checking the type of the next token.
*/

void	parse_expected_token(t_parser *p, e_token_type type)
{
	if (p->curr_token->type == type)
	{
		p->prev_token = p->curr_token;
		p->curr_token = get_next_token(p->lexer);
	}
	else
	{
		p->prev_token->value = p->curr_token->value;
		p->prev_token->type = illegal;
		p->curr_token = get_next_token(p->lexer);
	}
	// else
	// {
	// 	printf("minishell: syntax error near unexpected token %s\n",
	// 		p->curr_token->value);
	// 	//free before exit
	// 	exit(EXIT_FAILURE);
	// }
}

void	syntax_error(t_parser *p, e_token_type type)
{
	if ()
}

int	is_redirection(t_parser *p, char c)
{
	// check the current token
	if (c == 'c')
	{
		if (p->curr_token->type == great || p->curr_token->type == greater
			|| p->curr_token->type == less)
			return (1);
	}
	else // check the previous token
	{
		if (p->prev_token->type == great || p->prev_token->type == greater
			|| p->prev_token->type == less)
			return (1);
	}
	return (0);
}
