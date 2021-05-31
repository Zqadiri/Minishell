/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 13:48:18 by zqadiri           #+#    #+#             */
/*   Updated: 2021/05/31 12:20:24 by zqadiri          ###   ########.fr       */
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
	printf ("counter :[%d]\n", counter);
	printf ("<|line: %s|>\n", line);
	m->history = ft_split(line, '\n');
	// free(line);
	// free(m->buf);
	return (1);
}

int	get_str_cmd(t_index *m)
{
	/* DELETE */

	m->tc_cmd.cmd_dm = tgetstr("dm", NULL);
	m->tc_cmd.cmd_dl = tgetstr("dl", NULL);
	m->tc_cmd.cmd_de = tgetstr("de", NULL);
	m->tc_cmd.cmd_dc = tgetstr("dc", NULL);

	/* INSERT */

	m->tc_cmd.cmd_im = tgetstr("im", NULL);
	m->tc_cmd.cmd_ic = tgetstr("ic", NULL);
	m->tc_cmd.cmd_ei = tgetstr("ei", NULL);

	/* cursor & clear */
	
	m->tc_cmd.cmd_ce = tgetstr("ce", NULL);
	m->tc_cmd.cmd_le = tgetstr("le", NULL);

	return (1);
}

int ft_putc(int c)
{
	return write(1, &c, 1);
}

void	delete_char(t_index *m)
{
	m->delete_cur++;
	// printf ("--> cur [%d]\n", m->delete_cur);
	// printf ("--> line [%d]\n", ft_strlen(m->line));
	// printf ("--> line : %s\n", m->line);
	m->tc_cmd.cmd_dm = tigetstr("smdc");
	tputs(m->tc_cmd.cmd_dm, 1, ft_putc);
	m->tc_cmd.cmd_le = tigetstr("cub1");
	tputs(m->tc_cmd.cmd_le, 1, ft_putc);
	m->tc_cmd.cmd_dc = tigetstr("dch1");
	tputs(m->tc_cmd.cmd_dc, 1, ft_putc);
}

void	move_up(void)
{
	printf ("up\n");
	exit (0);
}

void	move_down(void)
{
	printf ("down\n");
	exit (0);
}

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