/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 10:56:25 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/01 14:49:37 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*tokenize_text(t_lexer *l, char *s)
{
	char	*str;
	char	*temp;

	if (!s)
		str = ft_strdup("");
	else
		str = ft_strdup(s);
	while (l->c != EOF && !ft_strchar("|;>< \"\'", l->c))
	{
		// printf("f:tokenize_token\tl->c = [%c]\n", l->c);
		temp = str;
		while (l->c == 32 && l->c != EOF)
			readchar(l);
		if (l->c == BSLASH || l->c == DOLLAR)
			str = check_string(l, str, 2);
		else if (l->c == EOF)
		{
			free(temp);
			return (str);
		}
		else
		{
			str = ft_strjoinchar(str, l->c);
			readchar(l);
			free(temp);
		}
	}
	// printf("f:tokenize_token\t last char = [%c]\n", l->c);
	// if (!ft_strcmp(str, " "))
	// 	return (NULL);
	// printf("00000f:tokenize_token\tl->c = [%c]\n", l->c);
	printf("f:tokenize_text\tstr = [%s]\n", str);
	// printf(">>>>>>>>>>>>f:string_token\t l->curpos << [%d]- [%c]\n", l->curpos, l->c);
	// printf(">>>>>>>>>>>>f:string_token\t l->bufsize << [%d]\n", l->bufsize);
	return (str);
}

char	*tokenize_dquoted_text(t_lexer *l)
{
	char	*str;
	char	*temp;

	readchar(l);
	if (l->c == EOF)
		no_quotes(l, DQUOTE);
	str = ft_strdup("");
	while (l->c != DQUOTE && l->c != EOF)
	{
		temp = str;
		check_string(l, str, 1);
		if (l->c == DOLLAR)
			str = ft_strjoin(str, envar_token(l));
		else
		{
			str = ft_strjoinchar(str, l->c);
			readchar(l);
		}
		free(temp);
	}
	no_quotes(l, DQUOTE);
	readchar(l);
	return (str);
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
		no_quotes(l, SQUOTE);
	readchar(l);
	return (str);
}

t_token	*string_token(t_lexer *l)
{
	char	*str;
	char	*temp;

	str = ft_strdup("");
	while (l->curpos <= l->bufsize && l->c != PIPE && l->c != SEMICOLON
			&& l->c != GREAT && l->c != LESS && l->c != EOF)
	{
		temp = str;
		if (l->c == DQUOTE)
			str = ft_strjoin(str, tokenize_dquoted_text(l));
		else if (l->c == SQUOTE)
			str = ft_strjoin(str, tokenize_squoted_text(l));
		else
			str = ft_strjoin(str, tokenize_text(l, NULL));
		free(temp);
		if (l->c == 32)
			return (ret_str(l, str, id));
		// printf("f:string_token\t l->curpos << [%d]\n", l->curpos, l->c);
		// printf("f:string_token\t l->bufsize << [%d]\n", l->bufsize);
		printf("f:string_token\t l->c = [%c]\n", l->c);
	}
	// printf("f:string_token\t character <<<<<<<<<<<<< [%c]\n", l->c);
	printf("f:string_token\tstr -> [%s]\n", str);
	return (ret_str(l, str, id));
}

t_token	*get_next_token(t_lexer *l)
{
	while (l->c != EOF && (l->curpos <= l->bufsize))
	{
		skip_space(l);
		if (l->c == EOF)
			break ;
		// printf("f:get_next_token\tl->c = [%c]\n", l->c);
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
