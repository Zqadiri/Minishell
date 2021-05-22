/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 13:44:58 by iidzim            #+#    #+#             */
/*   Updated: 2021/05/22 11:08:14 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*init_token(e_token_type type, char *s)
{
	t_token	*t;

	// printf("f:init_token\t[%s]\n", c);
	t = malloc(sizeof(t_token));
	if (!t)
		return (NULL);
	t->value = ft_strdup(s);
	t->type = type;
	return (t);
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

int	no_quotes(t_lexer *l, char c)
{
	if (l->c == EOF)
		printf("syntax error expected %c\n", c);
	//free + exit
	return (1);
}