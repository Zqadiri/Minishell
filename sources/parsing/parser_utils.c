/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 11:52:47 by iidzim            #+#    #+#             */
/*   Updated: 2021/09/05 19:34:05 by iidzim           ###   ########.fr       */
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
		free(p->lexer->buffer);
		free(p->curr_token->value);
		free(p);
		return (NULL);
	}
	if (p->curr_token->type == illegal)
		return (NULL);
	return (p);
}

char	*get_stop_word(t_parser *p)
{
	int		i;
	char	*s;
	char	*word;

	i = p->lexer->curpos - 1;
	s = ft_strdup(p->lexer->buffer);
	if (p->curr_token->is_quoted == 0)
	{
		while (s[i] != 32 && s[i] != '<')
			i--;
		word = ft_substr(s, i + 1, p->lexer->curpos - i + 1);
	}
	else
	{
		i--;
		while (s[i] != DQUOTE && s[i] != SQUOTE)
			i--;
		word = ft_substr(s, i + 1, p->lexer->curpos - i - 2);
	}
	printf("word = [%s]\n", word);
	return (word);
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
	char	*temp;

	if (p->curr_token->type == illegal)
		return (NULL);
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
		if (p->prev_token->type == here_doc)
		{
			temp = p->curr_token->value;
			p->curr_token->value = get_stop_word(p);
			free(temp);
		}
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
