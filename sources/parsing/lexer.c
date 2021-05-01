/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 13:44:58 by iidzim            #+#    #+#             */
/*   Updated: 2021/05/01 17:22:32 by iidzim           ###   ########.fr       */
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
	i = 0;
	while (s[i])
		i++;
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
		printf("error\n");
	while(l->readpos < l->bufsize && (l->c == SPACE || l->c == '\t' || l->c == '\n'))
		readchar(l);
}

t_token *create_token(t_token *t ,char *type, char c)
{
	// t_token  *t;

	// t = malloc(sizeof(t_token));
	// if (!t)
	// 	return (NULL);
	t->value = &c;
	t->type = type;
	return (t);
}

char *parse_dquoted(t_lexer *l)
{
	char *str;
	char *temp;
	
	// str = malloc(sizeof(char));
	// if (!str)
	// 	return (NULL);
	// str[0] = '\0';
	str = ft_strdup("");
	while (l->c != DQUOTE)
	{
		if (l->c == SLASH && peek_char(l) == DOLLAR)
			env_var(l);
		else if (l->c == SLASH && (!ft_strchar("\\$\"", l->c)))
			readchar(l);
		printf("current char before DQUOTE: <%c>\n", l->c);
		temp = str;
		str = ft_strjoinchar(str, l->c);
		readchar(l);
		free(temp);
		printf("test\ns <%s>\n", str);
	}
	readchar(l);
	return (str);
}

char *read_identifier(t_lexer *l)
{
	char *s;
	char *temp;
	int pos;

	if (!(s = malloc(sizeof(char) * 100)))
		return (NULL);
	pos = 0;
	while((isalnum(l->c) || ft_strchar(".\'_\"-/$\\", l->c)) && l->c != 32)
	{
		if (l->c == '\\') // add this case later
		{
			//check DQUOTE & SQUOTE & DOLLAR
			if (peek_char(l) == SQUOTE || peek_char(l) == DQUOTE ||
				peek_char(l) == DOLLAR || peek_char(l) == SLASH)
			{
				readchar(l);
				s[pos] = l->c;
			}
		}
		if (l->c == DQUOTE || l->c == SQUOTE)
		{
			readchar(l);
			temp = s;
			if (l->c == DQUOTE)
			// {
				// printf("s <%s>\n", s);
				s = ft_strjoin(s,parse_dquoted(l));
			// }
			// printf("s <%s>\n", s);
			// else
			// 	s = ft_strjoin(s,parse_squoted(l));
			// free(temp);
			break;
		}
		else
			s[pos] = l->c;
		printf("current char: |%c|\n", l->c);
		pos++;
		readchar(l);
	}
	printf("pos : %d\n", pos);
	s[pos] = '\0';
	// printf("[%s]\n", s);
	return (s);
}

int valid_cmd(char *s)
{	
	if (!ft_strcmp(s, "echo") || !ft_strcmp(s, "cd") || !ft_strcmp(s, "pwd")
		|| !ft_strcmp(s, "env") || !ft_strcmp(s, "export") || !ft_strcmp(s, "unset"))
		return (1);
	return (0);
	// add condition for built-in function
}

char *lookupident(char *s)
{
	int i;

	i = 0;
	if (valid_cmd(s))
		s = CMD;
	else if (s[i] == '-' && ft_isalpha(s[i+1]))
		s = OPTION;
	else
		s = ARG;
	return (s);
}

t_token *next_token(t_token *token, t_lexer *l)
{
	skip_space(l);
	if (l->c == '|')
	{
		if (peek_char(l) == SPACE || isalnum(peek_char(l)))
			token->type = "PIPE";
		else
			token->type = "ILLEGAL";
		token->value = &l->c;
	}
	else if (l->c == ';')
	{
		if (peek_char(l) == SEMICOLON || peek_char(l) == PIPE)
			token = create_token(token, "ILLEGAL", l->c);
		else
			token = create_token(token, "SEMICOLON", l->c);
	}
	else if (l->c == '>')
	{
		if (peek_char(l) == GREAT)
			token = create_token(token, "GREATER", l->c);
		else
			token = create_token(token, "GREAT", l->c);
	}
	else if (l->c == '<')
	{
		token = create_token(token, "LESS", l->c);
		//syntax error
	}
	else if (l->c == 0)
		token = create_token(token, "EOF", EOF);
	else  // add DQUOTE & SQUOTE & $
	{
		if (isalnum(l->c) || ft_strchar(".\'_\"-/$\\", l->c))
		{
			if (read_identifier(l))
			{
				token->value = read_identifier(l);
				token->type = lookupident(token->value);
			printf("token type >> %s - token value >> %s\n", token->type, token->value);
			}
		}
		else
			// Invalid character in input return NOTOKEN;
			token = create_token(token, "ILLEGAL", l->c);
	}
	return (token);
}

void lexer(t_lexer *l)
{
	t_token *tok;
	int size_tok;
	int i;

	i = 0;
	size_tok = 2;

	while (l->bufsize > l->curpos)
	{
		tok = malloc(sizeof(t_token) * size_tok);
		if (!tok)
			return ;
		next_token(tok, l);
		if (!ft_strcmp(tok->type, "ILLEGAL") || !ft_strcmp(tok->type, "EOF"))
			printf("^syntax error : %s\n", tok->value);
		else
		{
			// i++;
			size_tok++;
			//tok = realloc(tok, sizeof(t_token) * size_tok);
			free(tok);
			// tok = malloc(sizeof(t_token) * size_tok);
		}
	}
}
