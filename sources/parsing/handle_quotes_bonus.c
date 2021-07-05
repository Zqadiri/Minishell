/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 19:35:00 by iidzim            #+#    #+#             */
/*   Updated: 2021/07/05 12:30:50 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*tokenize_dquoted_text(t_lexer *l)
{
	char	*str;
	char	*temp;

	readchar(l);
	if (l->c == EOF)
		if (!multi_lines(l, DQUOTE))
			return (NULL);
	str = ft_strdup("");
	while (l->c != DQUOTE && l->c != EOF)
	{
		temp = str;
		// check_string(l, str, 1);
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
		str = ft_joinchar(str, l->c);
		readchar(l);
		free(temp);
	}
	if (l->c == SQUOTE)
		s += 1;
	if (l->c == EOF && s == 0)
		if (!multi_lines(l, SQUOTE))
			return (NULL);
	readchar(l);
	return (str);
}
