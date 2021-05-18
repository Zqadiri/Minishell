/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 16:40:16 by iidzim            #+#    #+#             */
/*   Updated: 2021/05/15 16:15:07 by zqadiri          ###   ########.fr       */
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