/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 11:00:28 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/04 19:24:08 by iidzim           ###   ########.fr       */
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
		return ;
	while (l->readpos <= l->bufsize && (l->c == 32
			|| l->c == '\t' || l->c == '\n'))
		readchar(l);
}

t_token	*ret_str(t_lexer *l, char *s, int type)
{
	if (type == greater)
		readchar(l);
	if (type == great || type == pip || type == semi || type == greater)
		readchar(l);
	return (init_token(type, s));
}

t_token	*ret_char(t_lexer *l, char c, e_token_type type)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (ret_str(l, str, type));
}
