/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 10:56:25 by iidzim            #+#    #+#             */
/*   Updated: 2021/07/05 12:30:50 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*dquoted_helper(t_lexer *l, char *str)
{
	char	*str2;
	char	*temp;

	if (l->c == EOF)
	{
		str2 = ft_strdup("\"");
		temp = str2;
		str2 = ft_strjoin(str2, str);
		free(temp);
		return (str2);
	}
	readchar(l);
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
	return (dquoted_helper(l, str));
}

char	*tokenize_squoted_text(t_lexer *l)
{
	char	*str;
	char	*str2;
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
		str2 = ft_strdup("'");
		temp = str2;
		str2 = ft_strjoin(str2, str);
		free(temp);
		return (str2);
	}
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
		if (l->c == DQUOTE)
			str = ft_strjoin(str, tokenize_dquoted_text(l));
		else if (l->c == SQUOTE)
			str = ft_strjoin(str, tokenize_squoted_text(l));
		else
		{
			s = ft_strdup("");
			str = ft_strjoin(str, tokenize_text(l, s));
		}
		free(temp);
		if (l->c == 32)
			return (ret_str(l, str, id));
	}
	return (ret_str(l, str, id));
}
