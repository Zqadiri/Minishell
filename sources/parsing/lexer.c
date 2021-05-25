/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 13:44:58 by iidzim            #+#    #+#             */
/*   Updated: 2021/05/25 11:22:25 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*init_token(e_token_type type, char *s)
{
	t_token	*t;

	t = malloc(sizeof(t_token));
	if (!t)
		return (NULL);
	t->value = ft_strdup(s);
	t->type = type;
	return (t);
}

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

char *check_string(t_lexer *l, char *str, int i)
{
	char *temp;
	
	if (i == 1)
	{
		if (l->c == BSLASH)
		{
			if (peek_char(l) == DQUOTE || peek_char(l) == DOLLAR
				|| peek_char(l) == BSLASH)
			{
				temp = str;
				readchar(l);
				str = ft_strjoinchar(str, l->c);
				readchar(l);
				free(temp);
			}
		}
	}
	if (i == 2)
	{
		if (l->c == BSLASH && peek_char(l) == EOF)
			no_quotes(l, '/');
		else
		// if (l->c =BSLAH)
			readchar(l);
		if (l->c == DOLLAR)
		{
			// printf("f:check_string\t[%c]\n", l->c);
			temp = str;
			str = ft_strjoin(str, envar_token(l));
			// printf("**f:check_string\tstr = [%s]\n", str);
			// free(temp);
		}
	}
	return (str);
}
