/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:27:47 by iidzim            #+#    #+#             */
/*   Updated: 2021/04/22 11:47:14 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		read_cmd(t);
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
        // printf("%s\n", t.buffer);
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