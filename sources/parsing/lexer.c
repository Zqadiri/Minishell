/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 13:44:58 by iidzim            #+#    #+#             */
/*   Updated: 2021/04/26 14:46:16 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void readchar(t_lexer *l)
{
	if (!l || !l->buffer)
		printf("error\n");
	if (l->readpos >= l->bufsize)
		l->c = EOF; //EOF
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
		// if (l->c == '\\') // add this case later
		// 	readchar(l);
		s[pos] = l->c;
		pos++;
		readchar(l);
		//check DQUOTE & SQUOTE
	}
	s[pos] = '\0';
	printf("[%s]\n", s);
	return (s);
}

int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int valid_cmd(char *s)
{
	if (!ft_strcmp(s, "echo"))
	{
	}
	else if (!ft_strcmp(s, "cd"))
	{ 
	}
	else if (!ft_strcmp(s, "pwd"))
	{
	}
	else if (!ft_strcmp(s, "export"))
	{
	}
	else if (!ft_strcmp(s, "unset"))
	{
	}
	else if (!ft_strcmp(s, "env"))
	{
	}
	else if (!ft_strcmp(s, "exit\n"))
	{
		exit(0);
	}
	else
		return (0);
	// add condition for built-in function
	return (1);
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

t_token *next_token(t_lexer *l)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
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
	else if (l->c == '\'')
	{
		token = create_token(token, "SQUOTE", l->c);
		//syntax error
	}
	else if (l->c == '\"')
	{
		token = create_token(token, "DQUOTE", l->c);
		//syntax error
	}
	else if (l->c == '$')
	{
		token = create_token(token, "DOLLAR", l->c);
		//syntax error
	}
	else if (l->c == 0)
		token = create_token(token, "EOF", EOF);
	else if (isalnum(l->c) || ft_strchar("._-/$\\", l->c))
	{
		token->value = read_identifier(l);
		token->type = lookupident(token->value);
		printf("token type >> %s - token value >> %s\n", token->type, token->value);
		// parse quoted text
	}
	else
		// Invalid character in input return NOTOKEN;
		token = create_token(token, "ILLEGAL", l->c);
	return (token);
}

void lexer(t_lexer *l)
{
	t_token *tok;
	t_token **t;
	int i;

	i = 0;
	t = malloc(sizeof(t_token));
	if (!t)
		return ;
	while (l->bufsize > l->curpos)
	{
		tok = next_token(l);
		// if (!ft_strcmp(tok->type, "ILLEGAL") || !ft_strcmp(tok->type, "EOF"))
		// 	printf("^syntax error : %s\n", tok->value);
		// else
		// 	printf("ok\n");
		// else
		// {
		// 	// realloc t 
		// 	// t = realloc(t, sizeof(t_token) * 2);
		// 	// add tok to t
		// 	// t[i]->type = tok->type;
		// 	// t[i]->value = tok->value;
		// 	// i++;
		// 	// printf("%d\n", i);
		// }
		// i = 0;
		// while(t)
		// {
		// 	printf("t[%d]->value: %s - t[%d]->type: %s\n", i, t[i]->value,i, t[i]->type);
		// 	i++;
		// }
	}
	
}
