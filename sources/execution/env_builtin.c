/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 15:56:12 by zqadiri           #+#    #+#             */
/*   Updated: 2021/07/10 16:59:30 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** env [without any options]
** is used to print environment variables
*/

int env_builtin(void)
{
    int i;

    i = 0; 
    while (g_global->env_var[i] != NULL)
    {
        ft_putendl_fd(g_global->env_var[i], 1);
        i++;
    }
	return (1);
}