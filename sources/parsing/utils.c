/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 10:21:43 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/04 11:56:26 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ftstrcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strjoinchar(char *s, char c)
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
	// free(s);
	return (str);
}

int	multi_lines(t_lexer *l, char c)
{
	if (l->c == BSLASH)
	{
		printf("minishell: syntax error multiple lines\n");
		l->multi_line = 1;
		return (0);
	}	
	if (l->c == EOF)
	{
		printf("minishell: syntax error expected %c\n", c);
		l->multi_line = 1;
		return (0);
	}
	return (1);
}


int	is_valid_id(char *str)
{
	int i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (!ft_isalpha(str[i]) && str[i] == '_')
			return (0);
	}
	return (1);
}
