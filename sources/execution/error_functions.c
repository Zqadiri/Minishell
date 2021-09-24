/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 14:46:46 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/24 11:18:39 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error(char *file_error)
{
	write (2, "minishell: ", 11);
	write(2, file_error, ft_strlen(file_error));
	perror(" ");
}

void	check_valid_fd(t_data *m, char *file_error, int fd)
{
	if (fd < 0)
	{
		m->redir->err = 1;
		write (2, "minishell: ", 11);
		write(2, file_error, ft_strlen(file_error));
		perror(" ");
		g_global->exit_status = 1;
	}
}

void	fork_failed(void)
{
	write(2, "Fork failed", 11);
	exit(EXIT_FAILURE);
}

void	not_valid_id(char *arg)
{
	write (2, "minishell: unset: `", 19);
	write (2, arg, ft_strlen(arg));
	write (2, "': not a valid identifier\n", 26);
	g_global->exit_status = 1;
}

void	error_retrieving_cd(void)
{
	ft_putstr_fd("cd: error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
	printf("%s\n", strerror(errno));
}