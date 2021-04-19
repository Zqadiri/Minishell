/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 12:17:00 by iidzim            #+#    #+#             */
/*   Updated: 2021/04/19 17:06:52 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void read_cmd(t_lexer *t)
{
	t_cmdlist l;
	char *line;

	line = ft_strdup("");
	while (get_next_line(0, &line) > 0)
	{
		t->buffer = ft_strdup(line);
		t->bufsize = ft_strlen(line);
		lexer(&l, t);
		// print_cmd(&l);
		free(line);
		free(t->buffer);
	}
	printf("exit\n");
	// printf("|%s| - %ld\n", t->buffer, t->bufsize);
}

//try to match the input with each of the regex.
void lexer(t_cmdlist *l, t_lexer *t)
{
	t_token **cmd;
	t_token *token;
	int i;
	// int pipe;
	
	printf("%s\n", t->buffer);
	i = 0;
	t->curpos = 0;
	cmd = NULL;
	while (t->bufsize > t->curpos)
	{
		token = malloc(sizeof(t_token));
		if (t->buffer[t->curpos] == 32)
			t->curpos++;
		// else if (t->buffer[t->curpos] == '|')
		// 	pipe = 1;
		// else if (t->buffer[t->curpos] == ';')
		// 	pipe = 0;
		else //abort
		{
			while (isalnum(t->buffer[t->curpos]))
			{
				printf("in\n");
				printf(">>%d\n", i);
				if (i == 0)
				{
					token->type = CMD;
					printf(">>%s\n", token->type);
				}
				else
				{
					token->type = "param";
					printf(">>%s\n", token->type);
				}
				token->value = "qwertyuio";
				printf("|%s|\n", token->value);
				token->value = strcat(token->value, &t->buffer[t->curpos]);
				printf("|%s|\n", token->value);
				t->curpos++;
				i++;
			}
		}
		t->curpos++;

	}
	printf("%d - %d\n", t->bufsize, t->curpos);
	// (void)l;
	if (!l->tokens)
		l = create(cmd, pipe);
	else
		add_back(&l, cmd, pipe);
	print_cmd(l);
}
// c.cmd[i] = token i