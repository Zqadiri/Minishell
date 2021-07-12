/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 10:56:25 by iidzim            #+#    #+#             */
/*   Updated: 2021/07/11 20:16:59 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	multi_lines(t_lexer *l, char c)
{
	if (l->c == BSLASH || l->c == EOF)
	{
		if (l->c == BSLASH)
			printf("minishell: syntax error multiple lines\n");
		if (l->c == EOF)
			printf("minishell: syntax error expected %c\n", c);
		l->multi_line = 1;
		return (0);
	}
	return (1);
}

char	*tokenize_text(t_lexer *l, char *s)
{
	char	*str;
	char	*temp;

	str = ft_strdup(s);
	while (l->c != EOF && !ft_strchar("|>< \"\'", l->c))
	{
		temp = str;
		while (l->c == 32 && l->c != EOF)
			readchar(l);
		if (l->c == DOLLAR)
			str = ft_strjoin(str, envar_token(l));
		else if (l->c == EOF)
		{
			free(temp);
			return (str);
		}
		else
		{
			str = ft_joinchar(str, l->c);
			readchar(l);
		}
		free(temp);
	}
	return (str);
}

char	*tokenize_dquoted_text(t_lexer *l)
{
	char	*str;
	char	*temp;

	readchar(l);
	str = ft_strdup("");
	while (l->c != DQUOTE && l->c != EOF)
	{
		temp = str;
		if (l->c == DOLLAR)
			str = ft_strjoin(str, envar_token(l));
		else
		{
			str = ft_joinchar(str, l->c);
			readchar(l);
		}
		free(temp);
	}
	if (!multi_lines(l, DQUOTE))
		return (NULL);
	l->is_quoted = 1;
	readchar(l);
	return (str);
}

char	*tokenize_squoted_text(t_lexer *l)
{
	char	*str;
	char	*temp;

	readchar(l);
	str = ft_strdup("");
	while (l->c != SQUOTE && l->c != EOF)
	{
		temp = str;
		str = ft_joinchar(str, l->c);
		readchar(l);
		free(temp);
	}
	if (l->c == EOF)
	{
		if (!multi_lines(l, SQUOTE))
			return (NULL);
	}
	l->is_quoted = 1;
	readchar(l);
	return (str);
}

t_token	*string_token(t_lexer *l)
{
	char	*str;
	char	*s;
	char	*temp;

	str = ft_strdup("");
	while (l->curpos <= l->bufsize && l->c != PIPE && l->c != GREAT
		&& l->c != LESS && l->c != EOF)
	{
		temp = str;
		s = ft_strdup("");
		if (l->c == DQUOTE)
			s = tokenize_dquoted_text(l);
		else if (l->c == SQUOTE)
			s = tokenize_squoted_text(l);
		else
			s = tokenize_text(l, s);
		if (!s && l->multi_line == 1)
			return (ret_str(l, NULL, illegal));
		str = ft_strjoin(str, s);
		free(s);
		free(temp);
		if (l->c == 32)
			return (ret_str(l, str, id));
	}
	return (ret_str(l, str, id));
}
