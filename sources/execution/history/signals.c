/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 13:48:18 by zqadiri           #+#    #+#             */
/*   Updated: 2021/06/07 13:22:08 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

int     get_history_file(t_index *m)
{
	int i;
	int counter;
	char	*line;
	char	*pfree;

	i = 0;
	counter = 0;
	// if (m->history)
	// 	free_array(m->history);
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
		pfree = line;
		line = ft_strjoinchar(line, m->buf[0]);
		free (pfree);
	}
	m->cursor = counter;
	m->history = ft_split(line, '\n');
	return (1);
}

int	get_str_cmd(t_index *m)
{
	/* DELETE */
	m->tc_cmd.cmd_dm = tgetstr("dm", NULL);
	m->tc_cmd.cmd_dl = tgetstr("dl", NULL);
	m->tc_cmd.cmd_ed = tgetstr("ed", NULL);
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

int	is_printable(t_index *m)
{
	if (m->buf[0] == '\t' || m->buf[0] == '\v' || m->buf[0] == '\f' || m->buf[0] == '\r')
	{
		m->buf[0] = ' ';
		return (1);
	}
	return (0);
}

void	delete_char(t_index *m)
{
	m->tc_cmd.cmd_dm = tigetstr("smdc");
	tputs(m->tc_cmd.cmd_dm, 1, ft_putc);
	m->tc_cmd.cmd_le = tigetstr("cub1");
	tputs(m->tc_cmd.cmd_le, 1, ft_putc);
	m->tc_cmd.cmd_dc = tigetstr("dch1");
	tputs(m->tc_cmd.cmd_dc, 1, ft_putc);
	m->tc_cmd.cmd_ed = tigetstr("rmdc");
	tputs(m->tc_cmd.cmd_ed, 1, ft_putc);
}

void	move_up(t_index *m, t_lexer *l)
{	
	char	*tmp;

	m->tc_cmd.cmd_dm = tigetstr("smdc");
	tputs(m->tc_cmd.cmd_dm, 1, ft_putc);
	m->tc_cmd.cmd_dl = tigetstr("dl1");
	tputs(m->tc_cmd.cmd_dl, 1, ft_putc);
	m->tc_cmd.cmd_ed = tigetstr("rmdc");
	tputs(m->tc_cmd.cmd_ed, 1, ft_putc);
	// printf("{%d}\n", len(m->history));
	// printf("{%d}\n", m->cursor);
	if (m->cursor - 1 != 0)
	{
		m->cursor--;
		ft_putstr_fd("minishell-1.0$ ", 0);
		tmp = m->line;
		// printf ("%d\n", m->cursor);
		m->line = ft_strdup(m->history[m->cursor]);
		l->buffer = ft_strdup(m->line);
		l->bufsize = ft_strlen(m->line);
		free (tmp);
		ft_putstr_fd(m->history[m->cursor], 0);
	}
	else
	{
		ft_putstr_fd("minishell-1.0$ ", 0);
		tmp = m->line;
		m->line = ft_strdup(m->history[0]);
		l->buffer = ft_strdup(m->line);
		l->bufsize = ft_strlen(m->line);
		free (tmp);
		ft_putstr_fd(m->history[0], 0);
	}
}

void	move_down(t_index *m, t_lexer *l)
{
	char	*tmp;

	m->tc_cmd.cmd_dm = tigetstr("smdc");
	tputs(m->tc_cmd.cmd_dm, 1, ft_putc);
	m->tc_cmd.cmd_dl = tigetstr("dl1");
	tputs(m->tc_cmd.cmd_dl, 1, ft_putc);
	m->tc_cmd.cmd_ed = tigetstr("rmdc");
	tputs(m->tc_cmd.cmd_ed, 1, ft_putc);
	if (m->cursor + 1 < len(m->history))
	{
		m->cursor++;
		ft_putstr_fd("minishell-1.0$ ", 0);
		tmp = m->line;
		m->line = ft_strdup(m->history[m->cursor]);
		l->buffer = ft_strdup(m->line);
		l->bufsize = ft_strlen(m->line);
		free (tmp);
		ft_putstr_fd(m->history[m->cursor], 0);
	}
	else
	{
		ft_putstr_fd("minishell-1.0$ ", 0);
		m->line = ft_strdup("\n");
		l->buffer = ft_strdup(m->line);
		l->bufsize = 0;
	}
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