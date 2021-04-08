/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:27:47 by iidzim            #+#    #+#             */
/*   Updated: 2021/04/08 17:25:42 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void print_prompt()
{
	printf("$ ");
	// printf("> "); //  escaped by a backslash character 
}

void read_cmd(t_cmd *x)
{
	char *line;
	
	line = ft_strdup("");
	while (get_next_line(0, &line, 100) > 0)
	{
		ft_strjoin(x->cmd_line, line);
		free(line);
	}
}

int main(int argc, char **argv, char **env)
{
	t_cmd x;

	printf("%d %s %s", argc, argv[0], env[0]);
	while(1)
	{
		write(1, "ok", 2);
		print_prompt();
		read_cmd(&x);
		if (!x.cmd_line)
			exit(EXIT_SUCCESS);
		if(x.cmd_line[0] == '\0' || strcmp(x.cmd_line, "\n") == 0)
        {
            free(x.cmd_line);
            continue;
        }
        if(strcmp(x.cmd_line, "exit\n") == 0)
        {
            free(x.cmd_line);
            break;
        }
		printf("%s\n", x.cmd_line);
        free(x.cmd_line);
		// x = parser_cmd(cmd_line);
		// exec_cmd(&x);
	}
	exit(EXIT_SUCCESS);
	return (0);
}