/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 11:52:47 by iidzim            #+#    #+#             */
/*   Updated: 2021/07/13 12:06:49 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parser	*init_parser(t_lexer *l)
{
	t_parser	*p;

	if (!l->buffer)
		return (NULL);
	p = malloc(sizeof(t_parser));
	if (!p)
		return (NULL);
	p->lexer = l;
	p->curr_token = get_next_token(l);
	p->prev_token = p->curr_token;
	if (p->curr_token->type == pip)
	{
		print_msg("minishell: syntax error near unexpected token 1",
			p->curr_token->value);
		return (NULL);
	}
	if (p->curr_token->type == illegal)
	{
		free_parser(p);
		g_global->exit_status = 258;
		return (NULL);
	}
	return (p);
}

/*
** expected_token() : primary purpose is to enforce the correctness of
** the order of tokens by checking the type of the next token.
*/

void	print_msg(char *str, char *var)
{
	printf("%s", str);
	if (var)
	{
		printf(" `");
		printf("%s", var);
		printf("'\n");
	}
	g_global->exit_status = 258;
}

int	is_redic(t_token *t)
{
	if (t->type == great || t->type == greater || t->type == less
		|| t->type == here_doc)
		return (1);
	return (0);
}

t_token	*check_token(t_parser *p, t_ast *ast)
{
	if (p->curr_token->type == illegal)
	{
		g_global->exit_status = 258;
		return (NULL);
	}
	if (!syntax_error(p))
		return (NULL);
	if (is_redic(p->prev_token))
	{
		if (p->curr_token->type != id)
		{
			print_msg("minishell: syntax error near unexpected token 2",
				p->curr_token->value);
			return (NULL);
		}
		ast->redir_nbr += 1;
	}
	return (p->curr_token);
}

int	syntax_error(t_parser *p)
{
	if (p->prev_token->type == pip && p->curr_token->type == pip)
	{
		print_msg("minishell: syntax error near unexpected token 3",
			p->prev_token->value);
		return (0);
	}
	if ((is_redic(p->prev_token) && p->curr_token->type == eof)
		|| (p->prev_token->type == pip && p->curr_token->type == eof))
	{
		print_msg("minishell: syntax error near unexpected token `newline'\n",
			NULL);
		return (0);
	}
	return (1);
}
