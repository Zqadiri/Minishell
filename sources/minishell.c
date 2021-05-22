/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:27:47 by iidzim            #+#    #+#             */
/*   Updated: 2021/05/22 11:11:30 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int main(int argc, char **argv, char **env)
{
	t_lexer *l; 
	t_parser *p;
	// t_ast *ast;

	(void)argc;
	(void)argv; 
	(void)env;
	// if (argc != 1)
	// 	exit(1);
	while(1)
	{
		ft_putstr_fd("\nminishell$ ", 0);
		l = read_cmd();
		// printf("|%s|\n", l->buffer);
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
		p = init_parser(l);
		// ast = parser(p);
		// ast = parser(p);
	}//free before exit
	exit(EXIT_SUCCESS);
}

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
