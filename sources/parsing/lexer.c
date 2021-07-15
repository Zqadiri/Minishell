/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 13:44:58 by iidzim            #+#    #+#             */
/*   Updated: 2021/07/14 15:20:45 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	readchar(t_lexer *l)
{
	if (!l || !l->buffer)
		printf("error\n");
	if (l->readpos >= l->bufsize)
		l->c = EOF;
	else
		l->c = l->buffer[l->readpos];
	l->curpos = l->readpos;
	l->readpos++;
}

t_token	*ret_str(t_lexer *l, char *s, int type)
{
	if (type == greater || type == here_doc)
		readchar(l);
	if (type == great || type == pip || type == here_doc
		|| type == greater || type == less)
		readchar(l);
	return (init_token(type, s, l));
}

void	skip_space(t_lexer *l)
{
	if (!l || !l->buffer)
		return ;
	while (l->readpos <= l->bufsize && (l->c == 32
			|| l->c == '\t' || l->c == '\n'))
		readchar(l);
	l->is_quoted = 0;
}

t_token	*get_next_token(t_lexer *l)
{
	while (l->c != EOF && (l->curpos <= l->bufsize))
	{
		skip_space(l);
		if (l->c == EOF)
			break ;
		if (l->c == PIPE)
			return (ret_str(l, &(l->c), pip));
		else if (l->c == GREAT)
		{
			if (peek_char(l) == GREAT)
				return (ret_str(l, ">>", greater));
			return (ret_str(l, &(l->c), great));
		}
		else if (l->c == LESS)
		{
			if (peek_char(l) == LESS)
				return (ret_str(l, "<<", here_doc));
			return (ret_str(l, &(l->c), less));
		}
		else
			return (string_token(l));
	}
	return (ret_str(l, NULL, eof));
}
