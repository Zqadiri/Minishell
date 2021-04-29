/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:27:47 by iidzim            #+#    #+#             */
/*   Updated: 2021/04/29 13:14:15 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void init_struct(t_lexer *l)
{
	l->buffer = NULL;
	l->bufsize = 0;
	l->c = ' ';
	l->curpos = 0;
	l->readpos = 0;
}

void read_cmd(t_lexer *l)
{
	char *line;

	init_struct(l);
	line = ft_strdup("");
	while (get_next_line(0, &line) > 0)
	{
		l->buffer = ft_strdup(line);
		l->bufsize = ft_strlen(line);
		free(line);
	}
}

// void read_cmd(t_lexer *l)
// {
// 	size_t r;
// 	char *line;

// 	line = malloc(sizeof(char) * 200);
// 	if (!line)
// 		return ;
// 	r = read(0, line, 200);
// 	line[r - 1] = '\0';
// 	l->buffer = ft_strdup(line);
// 	l->bufsize = ft_strlen(l->buffer);
// }

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

// tok->value = malloc(sizeof(char) * 2);
// tok->size = ft_strlen(tok->value);
// realloc(tok->value, tok->size * 2);
// tok->size *= 2;
// initalize a struct
// ft_memset(tok, 0, sizeof(t_token));

// add list for history