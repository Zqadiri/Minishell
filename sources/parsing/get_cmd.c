/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 12:17:00 by iidzim            #+#    #+#             */
/*   Updated: 2021/04/11 18:39:27 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void print_prompt()
{
	ft_putstr_fd("minishell$ ", 0);
	// printf("> "); //  printed by the shell when you enter a multi-line command
}

short valid_syntax(char *line)
{
	// int i;
	
	(void)line;
	// printf("%s\n", line);
	// i = 0;
	// while(line[i] != '\0')
	// {
    //     //skip white spaces
    //     if (line[i] == ' ' || line[i] == '\t')
    //         i++;
	// 	//check for delimiter character
	// 	if (line[i] == ';' || line[i] == '|')
	// 		return;
	// }
	return 1;
}

void read_cmd(t_source *t)
{
    char *line;
	char *temp;

    t->curpos = 0;
	t->bufsize = 0;
	t->buffer = ft_strdup("");
    line = ft_strdup("");
	while (get_next_line(0, &line) > 0)
	{
		temp = t->buffer;
        t->buffer = ft_strjoin(t->buffer, line);
		free(temp);
        free(line);
	}
    t->bufsize = ft_strlen(t->buffer);
    printf("|%s| - %ld\n", t->buffer, t->bufsize);

    //check syntax error
    if (valid_syntax(t))
	{	
		if(strcmp(t->buffer, "exit\n") == 0)
			// + free()
			exit(EXIT_SUCCESS);
		parse_cmd(t);
	}
	else
	{
		printf("bash: %s: command not found\n", t->buffer);
		// + free()
		exit(EXIT_FAILURE);
	}
}
