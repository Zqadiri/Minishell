/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 15:42:49 by zqadiri           #+#    #+#             */
/*   Updated: 2021/05/24 17:58:24 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"


int history(t_lexer *l)
{
	int         fd;
	void	*buf;

	buf = NULL;
	fd = open("test.txt", O_CREAT | O_APPEND | O_RDWR);
	ft_putendl_fd(l->buffer, fd);
	read(fd, buf, 100);
	printf("buff --> %s\n", buf);
	return (1);
}

// int main(void)
// {
// 	history();
// 	return (1);
// }