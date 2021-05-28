/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 15:42:49 by zqadiri           #+#    #+#             */
/*   Updated: 2021/05/28 18:26:35 by zqadiri          ###   ########.fr       */
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
	term->c_lflag &= ~ICANON;
	tcsetattr(0, TCSANOW, term);
}
void	reset_term(struct termios *old_attr)
{
	tcsetattr(0, TCSANOW, old_attr);
}

int history(t_lexer *l)
{
	int		fd;
	void	*buf;
	struct termios *old_attr;
	struct termios *term;

	buf = NULL;
	old_attr = (struct termios *)malloc(sizeof(struct termios));
	term = (struct termios *)malloc(sizeof(struct termios));
	// check_signals(l);
	// init_term();
	init_termios(old_attr, term);
	//read
	reset_term(old_attr);
	fd = open("history.txt", O_APPEND | O_CREAT | O_RDWR, S_IRWXU);
	ft_putendl_fd(l->buffer, fd);
	close(fd);
	return (1);
}