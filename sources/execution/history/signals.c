/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 13:48:18 by zqadiri           #+#    #+#             */
/*   Updated: 2021/05/28 18:38:32 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void    interrupt_program(int sig)
{
    
}

void    quit_program(int sig)
{
    
}

void    terminate_process(int sig)
{
    
}

int	check_signals()
{
    // ctrl + c
    signal(SIGINT, interrupt_program);
    // ctrl + /
    signal(SIGQUIT, quit_program);
	// ctrl + d
    signal(SIGTERM, terminate_process);
    
    return (1);

}