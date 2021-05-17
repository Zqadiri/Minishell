/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 15:56:12 by zqadiri           #+#    #+#             */
/*   Updated: 2021/05/17 11:01:59 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** env [without any options]
** is used to print environment variables
*/

int env_builtin()
{
    int i;

    i = 0; 
    while (g_env_var[i])
    {
        write (1, g_env_var[i], ft_strlen(g_env_var[i]));
        write (1, "\n", 1);
        i++;
    }
	return (1);
}