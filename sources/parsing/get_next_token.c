/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 10:56:25 by iidzim            #+#    #+#             */
/*   Updated: 2021/09/05 17:59:54 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	multi_lines(t_lexer *l, char c)
{
	if (l->c == EOF)
	{
		if (c == DQUOTE)
			print_msg("minishell: syntax error expected \"\n", NULL);
		else
			print_msg("minishell: syntax error expected \'\n", NULL);
		l->multi_line = 1;
		return (0);
	}
	return (1);
}

char	*tokenize_text(t_lexer *l, char *s)
{
	char	*str;

	str = ft_strdup(s);
	while (l->c != EOF && !ft_strchar("|>< \"\'", l->c))
	{
		while (l->c == 32 && l->c != EOF)
			readchar(l);
		if (l->c == DOLLAR)
			str = ft_joinfree(str, envar_token(l));
		else if (l->c == EOF)
			return (str);
		else
		{
			str = ft_joinchar(str, l->c);
			readchar(l);
		}
	}
	return (str);
}

char	*tokenize_dquoted_text(t_lexer *l)
{
	char	*str;

	readchar(l);
	str = ft_strdup("");
	while (l->c != DQUOTE && l->c != EOF)
	{
		if (l->c == DOLLAR)
			str = ft_joinfree(str, envar_token(l));
		else
		{
			str = ft_joinchar(str, l->c);
			readchar(l);
		}
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

	readchar(l);
	str = ft_strdup("");
	while (l->c != SQUOTE && l->c != EOF)
	{
		str = ft_joinchar(str, l->c);
		readchar(l);
	}
	if (!multi_lines(l, SQUOTE))
		return (NULL);
	l->is_quoted = 1;
	readchar(l);
	return (str);
}

t_token	*string_token(t_lexer *l)
{
	char	*str;
	char	*s;
	char	*temp2;

	str = ft_strdup("");
	while (l->curpos <= l->bufsize && l->c != PIPE && l->c != GREAT
		&& l->c != LESS && l->c != EOF)
	{
		s = ft_strdup("");
		temp2 = s;
		if (l->c == DQUOTE)
			s = tokenize_dquoted_text(l);
		else if (l->c == SQUOTE)
			s = tokenize_squoted_text(l);
		else
			s = tokenize_text(l, s);
		if (!s && l->multi_line == 1)
		{
			free(temp2);
			return (init_token(illegal, NULL, l));
		}
		str = ft_joinfree(str, s);
		free(temp2);
		if (l->c == 32)
		{
			t_token *t;
			t = init_token(id, str, l);
			free(str);
			return (t);
			// return (init_token(id, str, l));
		}
	}
	t_token *tok;
	tok = init_token(id, str, l);
	free(str);
	return (tok);
	// return (init_token(id, str, l));
}
