/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 11:52:47 by iidzim            #+#    #+#             */
/*   Updated: 2021/07/09 21:34:32 by iidzim           ###   ########.fr       */
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
	if (p->curr_token->type == pip)
	{
		printf("minishell: syntax error near unexpected token 1`%s'\n",
			p->curr_token->value);
		free_parser(p);
		return (NULL);
	}
	if (p->curr_token->type == illegal)
	{
		free_parser(p);
		return (NULL);
	}
	return (p);
}

/*
** expected_token() : primary purpose is to enforce the correctness of
** the order of tokens by checking the type of the next token.
*/

t_token	*check_token(t_parser *p, t_ast *ast)
{
	if (p->curr_token->type == illegal)
		return (NULL);
	if (!syntax_error(p))
		return (NULL);
	if (is_redic(p->prev_token))
	{
		if (!parse_expected_token(p, id))
			return (NULL);
		ast->redir_nbr += 1;
	}
	return (p->curr_token);
}

int	parse_expected_token(t_parser *p, t_token_type type)
{
	if (p->curr_token->type == type)
		return (1);
	else
	{
		printf("minishell: syntax error near unexpected token 2`%s'\n",
			p->curr_token->value);
		free_parser(p);
		return (0);
	}
	return (1);
}

int	syntax_error(t_parser *p)
{
	if ((p->prev_token->type == pip && p->curr_token->type == pip)
		|| (p->prev_token->type == pip && p->curr_token->type == eof))
	{
		printf("minishell: syntax error near unexpected token 3`%s'\n",
			p->curr_token->value);
		free_parser(p);
		return (0);
	}
	if (is_redic(p->prev_token) && p->curr_token->type == eof)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		free_parser(p);
		return (0);
	}
	return (1);
}

int	is_redic(t_token *t)
{
	if (t->type == great || t->type == greater || t->type == less
		|| t->type == here_doc)
		return (1);
	return (0);
}
