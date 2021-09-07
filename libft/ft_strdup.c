/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 00:38:49 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/07 18:59:12 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strdup(const char *src)
// {
// 	int		size;
// 	char	*p;
// 	int		i;

// 	i = 0;
// 	if (!src)
// 		return (NULL);
// 	size = ft_strlen(src) + 1;
// 	p = (char *)malloc(size * sizeof(char));
// 	if (p == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (src[i] != '\0')
// 	{
// 		*(p + i) = src[i];
// 		i++;
// 	}
// 	*(p + i) = '\0';
// 	return (p);
// }

char	*ft_strdup(const char *str)
{
	unsigned int	i;
	unsigned int	j;
	char			*cp;

	i = 0;
	j = -1;
	while (str[i] != '\0')
		i++;
	cp = (char *)malloc(sizeof(char) * (i + 1));
	if (!cp)
		return (NULL);
	while (++j < (sizeof(char) * i))
		cp[j] = str[j];
	cp[j] = '\0';
	return (cp);
}
