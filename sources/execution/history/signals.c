/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 13:48:18 by zqadiri           #+#    #+#             */
/*   Updated: 2021/05/30 16:43:08 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int     get_history_file(t_index *m)
{
	int i;
	int counter;
	char	*line;

	i = 0;
	counter = 0;
	// if (m->history != NULL)
	// 	ft_free(m->history);
	line = malloc(sizeof(char) * 2);
	line[0] = '\0';
	m->buf = malloc(sizeof(char) * 2);
	if (m->buf == NULL)
		return (-1);
	m->buf[1] = 0;
	while (read(m->fd, m->buf, 1))
	{
		if (m->buf[0] == '\n')
			counter++;
		line = ft_strjoinchar(line, m->buf[0]);	
	}
	m->cursor = counter;
	// printf("counter :[%d]\n", counter);
	// printf("<|line: %s|>\n", line);
	m->history = ft_split(line, '\n');
	// free(line);
	// free(m->buf);
	return (1);
	// m->history = (char **)malloc(sizeof(char *) * )
}

// int	get_str_cmd(t_index *m)
// {
	
// 	return (1);
// }

void    interrupt_program(int sig)
{
	(void)sig;
	printf("ctrl + c\n");
}

void    quit_program(int sig)
{
	(void)sig;
	printf("ctrl + \\ \n");
}

void    terminate_process(int sig)
{
	(void)sig;
	printf("ctrl + d\n");
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