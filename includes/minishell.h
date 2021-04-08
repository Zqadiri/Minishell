/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:28:30 by iidzim            #+#    #+#             */
/*   Updated: 2021/04/08 17:22:13 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define PATH_MAX 15000

typedef struct s_cmd
{
    char *cmd_line;
    char **token;
    char index;
}               t_cmd;

void print_prompt();
void read_cmd(t_cmd *x);
// t_cmd parser_cmd(char *cmd_line);
// void exec_cmd(t_cmd *x);


int		get_next_line(int fd, char **line, int buff_size);
int     ft_strlen(char *s);
char	*ft_strdup(char *str);
char	*ft_substr(char *s, int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);


#endif
