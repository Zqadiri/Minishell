/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:27:47 by iidzim            #+#    #+#             */
/*   Updated: 2021/04/26 14:45:46 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void read_cmd(t_lexer *t)
// {
// 	char *line;

// 	line = ft_strdup("");
// 	while (get_next_line(0, &line) > 0)
// 	{
// 		t->buffer = ft_strdup(line);
// 		t->bufsize = ft_strlen(line);
// 		t->curpos = 0;
// 		// t->readpos = t->curpos + 1;
// 		t->c = ' ';
// 		free(line);
// 	}
// }

void read_cmd(t_lexer *l)
{
	size_t r;

	l->buffer = malloc(sizeof(char) * 1024);
	if (!l->buffer)
		return ;
	r = read(0, l->buffer, 1024);
	l->buffer[r - 1] = '\0';
	l->bufsize = ft_strlen(l->buffer);
}

void init_struct(t_lexer *l)
{
	l->buffer = NULL;
	l->bufsize = 0;
	l->c = 0;
	l->curpos = 0;
	l->readpos = 0;
}

int main(int argc, char **argv, char **env)
{
	// t_cmdtable x;
	t_lexer *l;

	(void)argc;
	(void)argv; 
	(void)env;
	while(1)
	{
		ft_putstr_fd("minishell$ ", 0);
		l = malloc(sizeof(t_lexer));
		init_struct(l);
		// ft_memset(l, 0, sizeof(t_token));
		read_cmd(l);
		printf("|%s|\n", l->buffer);
		if(!l->buffer)
			exit(EXIT_SUCCESS);
		if(l->buffer[0] == '\0' || strcmp(l->buffer, "\n") == 0)
		{
			free(l);
			continue;
		}
		if(strcmp(l->buffer, "exit") == 0)
		{
			printf("exit\n");
			free(l);
			break;
		}
		lexer(l);
		// parse
		// execute
		free(l);
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