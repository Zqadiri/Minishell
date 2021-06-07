/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:27:47 by iidzim            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/06/06 14:05:57 by zqadiri          ###   ########.fr       */
=======
<<<<<<< HEAD
/*   Updated: 2021/06/06 21:41:48 by iidzim           ###   ########.fr       */
=======
/*   Updated: 2021/06/06 12:30:45 by zqadiri          ###   ########.fr       */
>>>>>>> da133498370b039815421eaf02ab501eeed5388e
>>>>>>> 1f513b4f31624040a719ae2743b5e692135cbbfc
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//* add new line 

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

int main(int argc, char **argv, char **env)
{
	t_lexer *l;
	t_parser *p;
	t_ast *ast;
	t_zineb *z;

	(void)argc;
	(void)argv; 
	(void)env;
	while(1)
	{
		// ? set return value to $? = 0  //!pipeline
		ft_putstr_fd("\nminishell-1.0$ ", 0);
		// l = read_cmd();
		l = history();
		// printf("\nl->buffer --%s--\n", l->buffer);
		// printf("l->bufsize --->|%d|\n", l->bufsize);
		if(!l->buffer)
			continue;
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
		p = init_parser(l);
		ast = parse_compound(p);
			
		// ? set exit status  $? = 258 (syntax error)
		// if (!ast)
			// $? = 258
		print_tree(ast);
		(void)z;
		z = visitor(ast);
		if (!z)
			return (0);
		print_zineb(z);
		if (ast)
			free_tree(ast);
		// system("leaks minishell");
	}
	//free before exit
	// exit(EXIT_SUCCESS);
	return (0);
}

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


// ! switch cmd name to lowercase before cmp


//? f:string_token  l-> = [;]
//? f:tokenize_token         last char = [;]
//? 00000f:tokenize_token   l->c = [;]
//? f:tokenize_text str = []
//? f:string_token  l-> = [;]
//? f:tokenize_token         last char = [;]
//? 00000f:tokenize_token   l->c = [;]
//? f:tokenize_text str = []


// ! filename -> cmd or delim
// ! previous -> current token
// ? l->buffer = |echo ok > |
// * semicolon at the end of line -> valid


//! tab  = 4 spaces
