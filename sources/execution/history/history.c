/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 15:42:49 by zqadiri           #+#    #+#             */
/*   Updated: 2021/05/29 16:36:41 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"


int	init_term(void)
{
	char	*term_type;
	int			ret;

	term_type = getenv("TERM");
	if (term_type == NULL)
	{
		ft_putendl_fd("TERM must be set",2);
		return (-1);		
	}
	ret = tgetent(NULL, term_type);
	if (ret == -1)
	{
		ft_putendl_fd(" the database is not accessible", 2);
		return (ret);		
	}
	if (ret == 0)
	{
		ft_putendl_fd("database does not contain any information for this type of terminal", 2);
		return (-1);
	}
	return (ret);
}

/* init terminfo */

int	Terminfo(void)
{
	int ret;

	ret = setupterm( NULL,  STDOUT_FILENO,  NULL);
	return (ret);
}

/*
** Changes the attributes associated with a terminal.
** New attributes are specified with a termios control structure.
** Programs should always issue a tcgetattr() first,
** modify the desired fields, and then issue a tcsetattr()
*/

void	init_termios(struct termios *term, struct termios *old_attr)
{
	char	*term_type;

	term_type = getenv("TERM");
	tgetent(NULL, term_type);
	tcgetattr(0, old_attr);
	tcgetattr(0, term);
	// set new attr
	term->c_lflag &= ~ECHO;
	// turns off canonical mode
	term->c_lflag &= ~ICANON;
	tcsetattr(0, TCSANOW, term);
}

void	reset_term(struct termios *old_attr)
{
	tcsetattr(0, TCSANOW, old_attr);
}

t_lexer	*init(t_lexer	*l)
{
	l = malloc(sizeof(t_lexer));
	if (!l)
		return (NULL);
	l->buffer = NULL;
	l->bufsize = 0;
	l->c = ' ';
	l->curpos = 0;
	l->readpos = 0;
	return (l);
}

void	read_char(t_index *m)
{
	init_termios(m->old_attr, m->term);
	read(0, m->buf, 1);
	printf("------>%d\n", m->buf[0]);
	reset_term(m->old_attr);
	
}

t_lexer *history(void)
{
	int		fd;
	t_index m;
	t_lexer *l;
	char	*line;
	char	*tmp;

	// int ret = 0;
	l = NULL;
	l = init(l);
	fd = open("history.txt", O_APPEND | O_CREAT | O_RDWR, S_IRWXU);
	m.old_attr = (struct termios *)malloc(sizeof(struct termios));
	m.term = (struct termios *)malloc(sizeof(struct termios));
	m.buf = malloc(sizeof(char) * 2);
	m.buf[1] = 0;
	check_signals(l);
	init_term();	
	line = malloc(sizeof(char) * 2);
	line[0] = '\0';
	while (1)
	{
		read_char(&m);
		if (m.buf[0] == 27)
		{
			read_char(&m);
			read_char(&m);
			if (m.buf[0] == 65)
			{
				printf("inA");
				exit (0);
			}
			else if (m.buf[0] == 66)
			{
				printf("inB");		
				exit (0);
			}
		}
		else if (m.buf[0] == '\n')
		{
			
			printf ("H line : [%s]\n", line);
			// write(fd, line, ft_strlen(line));
			ft_putendl_fd(line, fd);
			break ;
		}
		else
		{
			tmp = line;
			line = ft_strjoinchar(line, m.buf[0]);
			l->buffer = ft_strdup(line);
			l->bufsize = ft_strlen(line);
			printf("|%s|\n", l->buffer);
			free (tmp);
			printf ("line : [%s]\n", line);
		}
	}
	close(fd);
	return (l);
}