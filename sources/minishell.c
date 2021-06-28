/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:27:47 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/28 10:19:00 by iidzim           ###   ########.fr       */
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

// char	*to_lower(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] >= 65 && s[i] <= 90)
// 			s[i] += 32;
// 		i++;
// 	}
// 	return (s);
// }

// int	execution(t_cmd	*z)
// {
// 	int		i;
// 	char	*s;

// 	if (!z)
// 		return (NULL);
// 	i = -1;
// 	while (z[++i].argvs)
// 	{
// 		s = to_lower(z[i].argvs[0]);
// 		if (is_builtin(s))
// 			exec_cmd(z);
// 		else if (is_cmdpath(s))
// 			exec_cmd(z);
// 		else
// 		{
// 			printf("minishell: %s: command not found\n", z[i].argvs[0]);
// 			return (0);
// 		}
// 	}
// 	return (1);
// }

int main(int argc, char **argv, char **env)
{
	t_lexer *l;
	t_parser *p;
	t_ast *ast;
	t_cmd *z;

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
		if (p)
		{
			ast = parse_compound(p);
			// ? if (!ast) set exit status  $? = 258 (syntax error)
			// printf("\n------------------------------\n");
			// print_tree(ast);
			// printf("------------------------------\n\n");
			(void)z;
			z = visitor(ast);
			// execution(z);
			if (ast)
				free_tree(ast);
		}
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
