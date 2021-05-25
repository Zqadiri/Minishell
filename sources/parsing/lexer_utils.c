/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 11:00:28 by iidzim            #+#    #+#             */
/*   Updated: 2021/05/23 19:12:24 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	peek_char(t_lexer *l)
{
	if (l->readpos >= l->bufsize)
		return (EOF);
	else
		return (l->buffer[l->readpos]);
}

void	skip_space(t_lexer *l)
{
	if (!l || !l->buffer)
		return ; //error
	while (l->readpos < l->bufsize && (l->c == SPACE
			|| l->c == '\t' || l->c == '\n'))
		readchar(l);
}

t_token	*ret_char(t_lexer *l, char c, e_token_type type)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	if (type == greater)
		readchar(l);
	readchar(l);
	return (init_token(type, str));
}

t_token	*ret_str(t_lexer *l, char *s, int type)
{
	// printf("f:ret_str\t[%s]\n", s);
	if (type == greater)
		readchar(l);
	readchar(l);
	return (init_token(type, s));
}
