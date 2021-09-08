/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 10:21:43 by iidzim            #+#    #+#             */
/*   Updated: 2021/09/08 19:02:20 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*init_token(t_token_type type, char *s, t_lexer *l)
{
	t_token	*t;

	if (type == eof)
	{
		free(l->buffer);
		l->buffer = NULL;
	}
	t = malloc(sizeof(t_token));
	if (!t)
		return (NULL);
	if (s)
		t->value = ft_strdup(s);
		// free(s);//? bus on unknown address
	else
		t->value = NULL;
	t->type = type;
	t->is_quoted = l->is_quoted;
	return (t);
}

int	ftstrcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_joinchar(char *s, char c)
{
	int		i;
	char	*str;

	i = strlen(s);
	str = (char *)malloc(i + 2);
	if (!str)
		return (0);
	i = -1;
	while (s[++i])
		str[i] = s[i];
	str[i] = c;
	str[i + 1] = '\0';
	free(s);
	return (str);
}

int	is_valid_id(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (!ft_isalpha(str[i]) && str[i] == '_')
			return (0);
	}
	return (1);
}

char	*ft_joinfree(char *s1, char *s2)
{
	char	*s;

	if (!s2)
		return (s1);
	s = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (s);
}
