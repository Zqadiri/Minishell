/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:27:47 by iidzim            #+#    #+#             */
/*   Updated: 2021/04/08 14:34:12 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
    char *cmd_line;
    t_cmd x;

    while(1)
    {
        print_prompt();
        cmd_line = read_cmd();
        x = parser_cmd(cmd_line);
        exec_cmd(&x);
        exit(EXIT_SUCCESS);
    }
    return (0);
}