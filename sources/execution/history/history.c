/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 15:42:49 by zqadiri           #+#    #+#             */
/*   Updated: 2021/05/25 20:32:46 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// int	init_term()
// {
// 	char	*term_type;
// 	int			ret;

// 	term_type = getenv("TERM");
// 	ret = tgetent(NULL, term_type);
// 	// printf ("ret [%d]\n", ret);
// 	if (ret == 0)
// 	{
// 		// code 
// 		/* Termcap */
// 		// int column_count = tgetnum("co");
// 		// int line_count = tgetnum("li");

		
		
// 	}
// 	return (ret);
// }

int history(t_lexer *l)
{
	int		fd;
	void	*buf;

	buf = NULL;
	// init_term();
	fd = open("history.txt", O_APPEND | O_CREAT | O_RDWR, S_IRWXU);
	ft_putendl_fd(l->buffer, fd);
	close(fd);
	return (1);
}