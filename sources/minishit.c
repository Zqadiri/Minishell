/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:27:47 by iidzim            #+#    #+#             */
/*   Updated: 2021/04/11 18:26:48 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **env)
{
	t_cmd x;
	t_source t;

	(void)argc;
	(void)argv[0]; 
	(void)env[0];
	while(1)
	{
		ft_putstr_fd("minishell$ ", 0);
		read_cmd(&t);
		exec_cmd();
	}
	exit(EXIT_SUCCESS);
	return (0);
}

// ToDo List:
// read cmdline
// check if there is nay syntax error (eg: >>> or |; ...)
// implement functions (map) for linked list
 