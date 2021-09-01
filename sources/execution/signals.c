/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 10:59:46 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/01 18:10:08 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	interrupt_program(int sig)
{
	(void)sig;
	printf("ctrl + c\n");
}

void	quit_program(int sig)
{
	(void)sig;
	printf("ctrl + \\ \n");
}

void	terminate_process(int sig)
{
	(void)sig;
	printf("ctrl + d\n");
}

int	check_signals(void)
{
	signal(SIGINT, interrupt_program);
	signal(SIGQUIT, quit_program);
	signal(SIGTERM, terminate_process);
	return (1);
}
