/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 00:38:49 by zqadiri           #+#    #+#             */
/*   Updated: 2021/04/25 16:00:47 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		size;
	char	*p;
	int		i;

	i = 0;
	size = ft_strlen(src) + 1;
	p = (char *)malloc(size * sizeof(char));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		*(p + i) = src[i];
		i++;
	}
	*(p + i) = '\0';
	return (p);
}
