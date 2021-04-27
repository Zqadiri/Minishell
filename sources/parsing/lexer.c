/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 13:44:58 by iidzim            #+#    #+#             */
/*   Updated: 2021/04/27 17:13:18 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ftstrnstr(const char *str, const char *to_find, size_t len)
{
	size_t		i;
	char		*ptr;
	char		*find;
	size_t		size;

	i = 0;
	ptr = (char *)str;
	find = (char *)to_find;
	if (*to_find == '\0' || to_find == NULL)
		return (NULL);
	size = ft_strlen(find);
	while (ptr[i] != '\0' && len >= i + size)
	{
		if (ft_strncmp(ptr + i, find, size) == 0)
			return (ptr + i);
		i++;
	}
	return (NULL);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void readchar(t_lexer *l)
{
	if (!l || !l->buffer)
		printf("error\n");
	if (l->readpos >= l->bufsize)
		l->c = EOF;
	else
	{
		l->c = l->buffer[l->readpos];
		printf("current char: %c\n", l->c);
	}
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

t_token *create_token(t_token *token, char *type, char c)
{
	token->value = &c;
	token->type = type;
	return (token);
}

char *read_identifier(t_lexer *l)
{
	char *s;
	int pos;
	
	if (!(s = malloc(sizeof(char) * 100)))
		return (NULL);
	pos = 0;
	while(isalnum(l->c) || ft_strchar("._-/$\\", l->c))
	{
		if (l->c == '\\') // add this case later
			readchar(l);
		s[pos] = l->c;
		pos++;
		readchar(l);
		//check DQUOTE & SQUOTE & DOLLAR
	}
	s[pos] = '\0';
	printf("[%s]\n", s);
	return (s);
}

int valid_cmd(char *s)
{
	char *cmd = "echo cd pwd export unset env exit";
	
	if (ftstrnstr(cmd, s, ft_strlen(s)))
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
		s = PARAM;
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
			token->value = read_identifier(l);
			token->type = lookupident(token->value);
			printf("token type >> %s - token value >> %s\n", token->type, token->value);
			// parse quoted text
			
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
	tok = malloc(sizeof(t_token) * size_tok);
	if (!tok)
		return ;
	while (l->bufsize > l->curpos)
	{
		next_token(&tok[i], l);
		if (!ft_strcmp(tok->type, "ILLEGAL") || !ft_strcmp(tok->type, "EOF"))
			printf("^syntax error : %s\n", tok->value);
		else
		{
			i++;
			size_tok++;
			tok = realloc(tok, sizeof(t_token) * size_tok);
		}
	}
}
