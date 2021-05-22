/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 10:21:43 by iidzim            #+#    #+#             */
/*   Updated: 2021/05/22 20:17:02 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ftstrcmp(char *s1, char *s2)
{
	int i;

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
	if (!(str = (char *)malloc(i + 2)))
		return (0);
	i = -1;
	while (s[++i])
		str[i] = s[i];
	str[i] = c;
	str[i + 1] = '\0';
	// free(s);
	return (str);
}

int	no_quotes(t_lexer *l, char c)
{
	if (l->c == EOF)
	{
		printf("syntax error expected %c\n", c);
		//free + exit
		exit (1);
	}
	return (1);
}
