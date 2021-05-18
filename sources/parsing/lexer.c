/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 13:44:58 by iidzim            #+#    #+#             */
/*   Updated: 2021/05/18 11:57:23 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

t_token *init_token(int type, char *s)
{
	t_token  *t;

	t = malloc(sizeof(t_token));
	if (!t)
		return (NULL);
	t->value = s;
	t->type = type;
	return (t);
}

t_token *ret(t_lexer *l, char *s, int type)
{
	if (type == greater)
		readchar(l);
	readchar(l);
	// printf("f:ret\tstr >> |%s|\n", s);
	return (init_token(type, s));
}

int valid_envar(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char *tokenize_squoted_text(t_lexer *l)
{
	char *str;
	char *temp;
	
	readchar(l);
	str = ft_strdup("");
	while(l->c != SQUOTE && l->c != '\0')
	{
		temp = str;
		str = ft_strjoinchar(str, l->c);
		readchar(l);
		free(temp);
	}
	if (l->c == '\0')
		printf("syntax error->add \"\n"); //free + exit
	readchar(l);
	return (str);
}

char *tokenize_text(t_lexer *l)
{
	char *str;
	char *temp;

	if (!l)
		return (NULL);
	str = ft_strdup("");
	printf("f:tokenize_text\t<%c>\n", l->c);
	while (l->c != EOF && !ft_strchar("|;><", l->c))
	{
		temp = str;
		str = ft_strjoinchar(str, l->c);
		readchar(l);
		free(temp);
	}
	if (ft_strchar("|;><", l->c))
		printf("f:tokenize_text\tl->c > %c\n", l->c);
	printf("f:tokenize text <%s>\n", str);
	return (str);
}

char *envar_token(t_lexer *l)
{
	char *str;
	char *temp;

	if (!l)
		return (NULL);
	str = ft_strdup("");
	readchar(l);
	// if (ft_isdigit(l->c))
	// {
	// 	readchar(l);
	// 	return(tokenize_text(l));
	// }
	while (l->c != DQUOTE && l->c != '\0' && valid_envar(l->c)) 
	{
		temp = str;
		str = ft_strjoinchar(str, l->c);
		readchar(l);
		free(temp);
	}
	return (str);
}

char *tokenize_dquoted_text(t_lexer *l)
{
	char *str;
	char *temp;
	
	readchar(l);
	str = ft_strdup("");
	while(l->c != DQUOTE && l->c != '\0')
	{
		temp = str;
		if (l->c == SLASH)
		{
			readchar(l);
			if (l->c == DQUOTE || l->c == DOLLAR || l->c == SLASH)
			{
				str = ft_strjoinchar(str, l->c);
				readchar(l);
			}
		}
		else if (l->c == DOLLAR && ft_isdigit(peek_char(l)))
		{
			readchar(l);
			readchar(l);
		}
		else if (l->c == DOLLAR)// && !ft_isdigit(peek_char(l)))
			str = envar_token(l);
		else
		{
			str = ft_strjoinchar(str, l->c);
			readchar(l);
		}
		free(temp);
	}
	if (l->c == '\0')
		printf("syntax error->add \"\n"); //free + exit
	readchar(l);
	return (str);
}

t_token *string_token(t_lexer *l)
{
	char *str;
	char *temp;
	int i = 0;

	str = ft_strdup("");
	while (l->curpos < l->bufsize)/* && (l->c != PIPE || l->c != SEMICOLON
		|| l->c != GREAT|| l->c != LESS))*/
	{
		printf("f:string_token\ti = %d\n", i++);
		temp = str;
		if (l->c == DQUOTE)
		{
			str = ft_strjoin(str, tokenize_dquoted_text(l));
			free(temp);
			readchar(l);
			continue;
		}
		else if (l->c == SQUOTE)
		{
			str = ft_strjoin(str, tokenize_squoted_text(l));
			free(temp);
			readchar(l);
			continue;
		}
		else
		{
			str = ft_strjoin(str, tokenize_text(l));
			free(temp);
			readchar(l);
			continue;
		}
	}
	printf("f:string_token\tstr >> |%s|\n", str);
	return(ret(l, str, id));
}

t_token *get_next_token(t_lexer *l)
{
	while (l->c != EOF && (l->curpos < l->bufsize))
	{
		skip_space(l);
		printf("f:get_next_token\tcurrent char >%c\n", l->c);
		if (l->c == PIPE)
			return(ret(l, &l->c, pip));
		else if (l->c == SEMICOLON)
			return(ret(l, &l->c, semi));
		else if (l->c == GREAT)
		{
			if (peek_char(l) == GREAT)
				return(ret(l, ">>", greater));
			return(ret(l, &l->c, great));
		}
		else if (l->c == LESS)
			return(ret(l, &l->c, less));
		else
			return(string_token(l));
	}
	return(ret(l, &l->c, eof));
}
