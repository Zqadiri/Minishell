/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 13:44:58 by iidzim            #+#    #+#             */
/*   Updated: 2021/04/29 17:01:42 by iidzim           ###   ########.fr       */
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

char *parse_dquoted(t_lexer *l)
{
	char *str;
	// int nbr_squote = 0;
	// int nbr_dquote = 0;
	// int start;
	
	// start = l->curpos - 1;
	// while (++start > l->bufsize)
	// {
	// 	if (l->c == SQUOTE1)
	// 		nbr_squote++;
	// 	else
	// 		nbr_dquote++;	
	// }
	// if ((nbr_dquote % 2) != 0 || (nbr_squote % 2) != 0)
	// {
	// 	printf("syntax error\n");
	// 	return (0);
	// }
	readchar(l);
	while (l->c != DQUOTE)
	{
		//join l->c to str
		readchar(l);
	}
	return (str);
}

char *read_identifier(t_lexer *l)
{
	char *s;
	int pos;

	if (!(s = malloc(sizeof(char) * 100)))
		return (NULL);
	pos = 0;
	while(isalnum(l->c) || ft_strchar(".\'_\"-/$\\", l->c))
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
			s[pos] = l->c;
			readchar(l);
		}
		if (l->c == DQUOTE)
			parse_dquoted(l);
		if (l->c == SQUOTE)
			parse_squoted(l);
		s[pos] = l->c;
		pos++;
		readchar(l);
	}
	s[pos] = '\0';
	printf("[%s]\n", s);
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
			// parse quoted text
			// int nbr_squote = 0, nbr_dquote = 0;
			// if (l->c == SQUOTE)
			// {
			// 	nbr_squote += 1;
						
			// }
			// else if (l->c == DQUOTE)
			// {
			// 	nbr_dquote += 1;
				
			// }
			// else
			// {
				token->value = read_identifier(l);
				token->type = lookupident(token->value);
			// }
			printf("token type >> %s - token value >> %s\n", token->type, token->value);
			
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
