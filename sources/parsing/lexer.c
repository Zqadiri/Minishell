/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 13:44:58 by iidzim            #+#    #+#             */
/*   Updated: 2021/05/02 12:05:31 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strjoinchar(char *s, char c)
{
	int		i;
	char	*str;

	i = strlen(s);
	if (!(str = (char *)malloc(i + 2)))
		return (0);
	i = -1;
	while (s[++i])
		str[i] = s[i];
	str[i] = c;
	str[i + 1] = '\0';
	// free(s);
	return (str);
}

void readchar(t_lexer *l)
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

int peek_char(t_lexer *l)
{
	if (l->readpos >= l->bufsize)
		return (EOF);
	else
		return (l->buffer[l->readpos]);
}

void skip_space(t_lexer *l)
{
	if (!l || !l->buffer)
		return ; //error
	while(l->readpos < l->bufsize && (l->c == SPACE || l->c == '\t' || l->c == '\n'))
		readchar(l);
}

t_token *init_token(char *type, char *c)
{
	t_token  *t;

	t = malloc(sizeof(t_token));
	if (!t)
		return (NULL);
	t->value = c;
	t->type = type;
	return (t);
}

t_token *ret(t_lexer *l, int type)
{
	if (type == "GREATER")
		readchar(l);
	readchar(l);
	return (init_token(type, l->c));
}

t_token *tokenize_dquoted_text(t_lexer *l)
{
	char *str;
	char *temp;
	
	str = ft_strdup("");
	while(l->c != SQUOTE)
	{
		
	}
	readchar(l);
	init_token(ARG, str);
}

t_token *tokenize_squoted_text(t_lexer *l)
{
	char *str;
	char *temp;
	
	str = ft_strdup("");
	while(l->c != SQUOTE)
	{
		
	}
	readchar(l);
	init_token("argument", str);
}

t_token *tokenize_text(t_lexer *l)
{
	if (!l)
		return (NULL);
	while(isalnum(l->c) || ft_strchar("._-/$\\", l->c))
	{
		
	}
}

t_token *get_next_token(t_lexer *l)
{
	while (l->c != EOF && (l->curpos < l->bufsize))
	{
		skip_space(l);
		if (isalnum(l->c) || ft_strchar("._-/$\\", l->c))
			return(tokenize_text(l));
		if (l->c == DQUOTE)
			return (tokenize_dquoted_text(l));
		if (l->c == SQUOTE)
			return (tokenize_squoted_text(l));
		//switch cases:
		if (l->c == PIPE)
			return(ret(l, PIPE));
		else if (l->c == SEMICOLON)
			return(ret(l, SEMICOLON));
		else if (l->c == GREAT)
		{
			if (peek_char(l) == GREAT)
				return(ret(l, GREATER));
			return(ret(l, GREAT));
		}
		else if (l->c == LESS)
			return(ret(l, LESS));
	}
	return(ret(l,EOF));
}