/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 13:44:58 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/05 17:18:05 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*init_lexer(char *line)
{
	t_lexer	*l;

	l = malloc(sizeof(t_lexer));
	if (!l)
		return (NULL);
	l->buffer = ft_strdup(line);
	l->bufsize = ft_strlen(line);
	l->c = ' ';
	l->curpos = 0;
	l->readpos = 0;
	return (l);
}

int	valid_envar(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*invalid_envar(t_lexer *l, char *str)
{
	char	*temp;

	temp = str;
	if (l->c == '0')
		str = ft_strjoin(str, "minishell");
	if (l->c == '?')
		str = ft_strjoin(str, "$?");
	free(temp);
	readchar(l);
	return (tokenize_text(l, str));
}

char	*envar_token(t_lexer *l)
{
	char	*str;
	char	*temp;

	if (!l)
		return (NULL);
	str = ft_strdup("");
	readchar(l);
	if (ft_isdigit(l->c) || l->c == '?')
		return (invalid_envar(l, str));
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

char	*check_string(t_lexer *l, char *str, int i)
{
	if (i == 1 && l->c == BSLASH)
	{
		if (peek_char(l) == '\"' || peek_char(l) == '$' || peek_char(l) == '\\')
		{
			readchar(l);
			str = ft_strjoinchar(str, l->c);
		}
	}
	if (i == 2 && l->c == BSLASH)
	{
		if (peek_char(l) == EOF)
			multi_lines(l, '\\');
		else
		{
			readchar(l);
			str = ft_strjoinchar(str, l->c);
		}
		readchar(l);
		return (str);
	}
	if (i == 2 && l->c == DOLLAR)
		str = ft_strjoin(str, envar_token(l));
	return (str);
}
