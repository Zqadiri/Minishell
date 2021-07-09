/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 13:44:58 by iidzim            #+#    #+#             */
/*   Updated: 2021/07/09 20:48:34 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_space(t_lexer *l)
{
	if (!l || !l->buffer)
		return ;
	while (l->readpos <= l->bufsize && (l->c == 32
			|| l->c == '\t' || l->c == '\n'))
		readchar(l);
}

t_token	*ret_str(t_lexer *l, char *s, int type)
{
	if (type == greater || type == here_doc)
		readchar(l);
	if (type == great || type == pip || type == here_doc
		|| type == greater || type == less)
		readchar(l);
	return (init_token(type, s));
}

t_token	*ret_char(t_lexer *l, char c, t_token_type type)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (ret_str(l, str, type));
}

t_token	*get_next_token(t_lexer *l)
{
	while (l->c != EOF && (l->curpos <= l->bufsize))
	{
		skip_space(l);
		if (l->c == EOF)
			break ;
		if (l->c == PIPE)
			return (ret_char(l, l->c, pip));
		else if (l->c == GREAT)
		{
			if (peek_char(l) == GREAT)
				return (ret_str(l, ">>", greater));
			return (ret_char(l, l->c, great));
		}
		else if (l->c == LESS)
		{
			if (peek_char(l) == LESS)
				return (ret_str(l, "<<", here_doc));
			return (ret_char(l, l->c, less));
		}
		else
			return (string_token(l));
	}
	return (ret_char(l, l->c, eof));
}
