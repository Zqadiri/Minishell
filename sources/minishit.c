/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:27:47 by iidzim            #+#    #+#             */
/*   Updated: 2021/04/08 18:01:00 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void print_prompt()
{
	ft_putstr_fd("minishell$ ", 0);
	// printf("> "); //  escaped by a backslash character 
}

void read_cmd(t_cmd *x)
{
	char *line;
	
	line = ft_strdup("");
	while (get_next_line(0, &line) > 0)
	{
		ft_strjoin(x->cmd_line, line);
		free(line);
	}
}

int main(int argc, char **argv, char **env)
{
	t_cmd x;

	(void)argc;
	(void)argv[0]; 
	(void)env[0];
	while(1)
	{
		print_prompt();
		read_cmd(&x);
		printf("cmd \n");
		printf("%s\n", x.cmd_line);
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