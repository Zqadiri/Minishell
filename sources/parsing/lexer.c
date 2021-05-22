/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 13:44:58 by iidzim            #+#    #+#             */
/*   Updated: 2021/05/21 21:40:41 by iidzim           ###   ########.fr       */
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

t_token	*init_token(e_token_type type, char *s)
{
	t_token	*t;

	// printf("f:init_token\t[%s]\n", c);
	t = malloc(sizeof(t_token));
	if (!t)
		return (NULL);
	t->value = ft_strdup(s);
	t->type = type;
	return (t);
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
	printf("f:ret_str\t[%s]\n", s);
	if (type == greater)
		readchar(l);
	readchar(l);
	return (init_token(type, s));
}

int	valid_envar(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*tokenize_squoted_text(t_lexer *l)
{
	char	*str;
	char	*temp;
	int		s;

	s = 0;
	readchar(l);
	str = ft_strdup("");
	while (l->c != SQUOTE && l->c != EOF)
	{
		temp = str;
		str = ft_strjoinchar(str, l->c);
		readchar(l);
		free(temp);
	}
	if (l->c == SQUOTE)
		s += 1;
	if (l->c == EOF && s == 0)
		printf("syntax error expected token \'\n"); //free + exit
	readchar(l);
	return (str);
}

char	*envar_token(t_lexer *l)
{
	char	*str;
	char	*temp;

	if (!l)
		return (NULL);
	str = ft_strdup("");
	readchar(l);
	if (ft_isdigit(l->c))
	{
		if (l->c == '0')
			str = ft_strjoin(str, "minishell");
		readchar(l);
		return (tokenize_text(l, str));
	}
	while (valid_envar(l->c) && l->c != EOF)
	{
		temp = str;
		str = ft_strjoinchar(str, l->c);
		readchar(l);
		free(temp);
	}
	str = getenv(str);
	if (!str)
		str = ft_strdup("");
	return (str);
}

char	*tokenize_text(t_lexer *l, char *s)
{
	char	*str;
	char	*temp;

	if (!l)
		return (NULL);
	if (!s)
		str = ft_strdup("");
	else
		str = ft_strdup(s);
	while (l->c != EOF && !ft_strchar("|;>< ", l->c))
	{
		temp = str;
		if (l->c == DOLLAR)
			str = ft_strjoin(str, envar_token(l));
		if (l->c == EOF)
		{
			free(temp);
			return (str);
		}
		str = ft_strjoinchar(str, l->c);
		readchar(l);
		free(temp);
	}
	// printf("f:tokenize text22 <%s>\n", str);
	return (str);
}

char	*tokenize_dquoted_text(t_lexer *l)
{
	char	*str;
	char	*temp;

	readchar(l);
	str = ft_strdup("");
	while (l->c != DQUOTE && l->c != '\0')
	{
		temp = str;
		if (l->c == BSLASH)
		{
			readchar(l);
			if (l->c == DQUOTE || l->c == DOLLAR || l->c == BSLASH)
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
		else if (l->c == DOLLAR)
			str = envar_token(l);
		else
		{
			str = ft_strjoinchar(str, l->c);
			readchar(l);
		}
		free(temp);
	}
	if (l->c == '\0')
		printf("syntax error expected \"\n"); //free + exit
	readchar(l);
	return (str);
}

t_token	*string_token(t_lexer *l)
{
	char	*str;
	char	*temp;

	str = ft_strdup("");
	while (l->curpos < l->bufsize && (l->c != PIPE || l->c != SEMICOLON
		|| l->c != GREAT|| l->c != LESS))
	{
		temp = str;
		if (l->c == DQUOTE)
			str = ft_strjoin(str, tokenize_dquoted_text(l));
		else if (l->c == SQUOTE)
			str = ft_strjoin(str, tokenize_squoted_text(l));
		else
		{
			str = ft_strjoin(str, tokenize_text(l, NULL));
			printf("f:string_token\t-%s-\n", str);
		}
		free(temp);
		if (l->c == 32)
			return(ret_str(l, str, id));
		readchar(l);
		// continue;
	}
	// printf("f:string_token\tstr >> |%s|\n", str);
	return(ret_str(l, str, id));
}

t_token	*get_next_token(t_lexer *l)
{
	while (l->c != EOF && (l->curpos < l->bufsize))
	{
		skip_space(l);
		// printf("f:get_next_token\tcurrent char [%c]\n", l->c);
		if (l->c == PIPE)
			return (ret_char(l, l->c, pip));
		else if (l->c == SEMICOLON)
			return (ret_char(l, l->c, semi));
		else if (l->c == GREAT)
		{
			if (peek_char(l) == GREAT)
				return (ret_str(l, ">>", greater));
			return (ret_char(l, l->c, great));
		}
		else if (l->c == LESS)
			return (ret_char(l, l->c, less));
		else
			return (string_token(l));
	}
	return (ret_char(l, l->c, eof));
}
