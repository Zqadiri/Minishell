/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:27:47 by iidzim            #+#    #+#             */
/*   Updated: 2021/05/23 16:39:36 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*read_cmd(void)
{
	size_t	r;
	char	*line;
	char	*buffer;

	buffer = malloc(sizeof(char) * 2);
	r = read(0, buffer, 1);
	line = malloc(sizeof(char) * 2);
	if (!buffer || !line)
		return (NULL);
	line[0] = '\0';
	while (r > 0)
	{
		buffer[1] = 0;
		if (buffer[0] == '\n')
			break ;
		line = ft_strjoinchar(line, buffer[0]);
		r = read(0, buffer, 1);
	}
	free(buffer);
	return (init_lexer(line));
}

// int main(int argc, char **argv, char **env)
// {
// 	t_lexer *l; 
// 	t_parser *p;
// 	// t_ast *ast;

// 	(void)argc;
// 	(void)argv; 
// 	(void)env;
// 	// if (argc != 1)
// 	// 	exit(1);
// 	while(1)
// 	{
// 		ft_putstr_fd("\nminishell-3.2$ ", 0);
// 		l = read_cmd();
// 		// printf("|%s|\n", l->buffer);
// 		if(!l->buffer)
// 			exit(EXIT_SUCCESS);
// 		if(l->buffer[0] == '\0' || strcmp(l->buffer, "\n") == 0)
// 		{
// 			free(l);
// 			continue;
// 		}
// 		if(strcmp(l->buffer, "exit") == 0)
// 		{
// 			printf("exit\n");
// 			free(l);
// 			break;
// 		}
// 		p = init_parser(l);
// 		// ast = parser(p);
// 		// ast = parser(p);
// 	}//free before exit
// 	exit(EXIT_SUCCESS);
// }

// ToDo List:
// read cmdline √
// check if there is nay syntax error (eg: >>> or |; ...)
// implement functions (map) for linked list
// example :							 output
// √- echo c'o\'u'cou'					-> co\ucou 
// √- ec"ho" bon"'j'o'u"r				-> bon'j'o'ur
// √- ec"ho" bon"j'o\'u"r				-> bonj'o\'ur
// √- echo co'c"o"u'					-> coc"o"u
// √- echo co'"c\"o"u'					-> co"c\"o"u
// √- ec"ho" bon"jo"u"r					-> add " f next line ->bonjour
// √- ec"ho" bon"jo\"u"r					-> bonjo"ur
// √- echo bo'njou\$r					-> add ' f next line ->bonjou\$r
// √- echo bo"njou\$r					-> add " f next line ->bonjou$r
// √- ec"ho" bon"jo\"u"r					-> bonjo"ur
// √- echo "\\"							-> \
// √- bash-3.2$ echo A B C
// >>A B C
// √- bash-3.2$ echo A''B''C
// >>ABC
// - bash-3.2$ echo A '' B '' C
// >>A  B  C
// - bash-3.2$ echo A  B  C
// >>A B C

// /!\ A single quote may not occur between single quotes, even when preceded by a backslash.

// bash-3.2$ echo $SHELL
// /bin/zsh
// bash-3.2$ echo $_
// /bin/zsh
// bash-3.2$ echo $?
// 0

//bash-3.2$ export number="0 1  2       3"
// bash-3.2$ env | less
// bash-3.2$ echo "$number"
// 0 1  2       3
// bash-3.2$ echo $number - trim environment variable
// 0 1 2 3
// -> $IFS default separators used for field splitting 


// 123"456\""789