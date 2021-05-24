/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 15:31:05 by zqadiri           #+#    #+#             */
/*   Updated: 2021/05/23 19:12:24 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int quit(void)
{
    // free
    write(1, "\n", 1);
	exit(0);
}

int		len(char **env)
{
	register int	len;

	len = 0;
	while (env[len])
		len++;
	return (len);
}

int		alpha(char *key)
{
	int i;

	i = 0;
	while (key[i] != '\0')
	{
        if (ft_isalpha(key[i]))
		    i++;
        else
            return (-1);
	}
	return (1);
}