/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:27:47 by iidzim            #+#    #+#             */
/*   Updated: 2021/04/25 17:12:12 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void read_cmd(t_lexer *t)
{
	char *line;

	line = ft_strdup("");
	while (get_next_line(0, &line) > 0)
	{
		t->buffer = ft_strdup(line);
		t->bufsize = ft_strlen(line);
		t->curpos = 0;
		t->readpos = t->curpos + 1;
		t->c = ' ';
		free(line);
	}
}

void init_struct(t_lexer *t)
{
	t->buffer = NULL;
	t->bufsize = 0;
	t->c = 0;
	t->curpos = 0;
	t->readpos = 0;
}

int main(int argc, char **argv, char **env)
{
	// t_cmdtable x;
	t_lexer *t;

	(void)argc;
	(void)argv; 
	(void)env;
	while(1)
	{
		ft_putstr_fd("minishell$ ", 0);
		t = malloc(sizeof(t_lexer));
		init_struct(t);
		read_cmd(t);
		// printf("<<%s>>\n", t->buffer);
		if(!t->buffer)
			exit(EXIT_SUCCESS);
		if(t->buffer[0] == '\0' || strcmp(t->buffer, "\n") == 0)
		{
			free(t);
			continue;
		}
		if(strcmp(t->buffer, "exit\n") == 0)
		{
			printf("exit\n");
			free(t);
			break;
		}
		lexer(t);
		// parse
		// execute
		free(t);
	}
	exit(EXIT_SUCCESS);
}

// ToDo List:
// read cmdline √
// check if there is nay syntax error (eg: >>> or |; ...)
// implement functions (map) for linked list
// example :							 output
// - echo c'o\'u'cou'					-> co\ucou
// - ec"ho" bon"'j'o'u"r				-> bon'j'o'ur
// - ec"ho" bon"j'o\'u"r				-> bonj'o\'ur
// - echo co'c"o"u'						-> coc"o"u
// - echo co'"c\"o"u'					-> co"c\"o"u
// - ec"ho" bon"jo"u"r					-> add " f next line ->bonjour
// - ec"ho" bon"jo\"u"r					-> bonjo"ur
// - echo bo'njou\$r					-> add ' f next line ->bonjou\$r
// - echo bo"njou\$r					-> add " f next line ->bonjou$r
// - ec"ho" bon"jo\"u"r					-> bonjo"ur
// - echo "\\"							-> \

// bash-3.2$ echo A B C
// >>A B C
// bash-3.2$ echo A''B''C
// >>ABC
// bash-3.2$ echo A '' B '' C
// >>A  B  C
// bash-3.2$ echo A  B  C
// >>A B C