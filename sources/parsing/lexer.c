/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 13:44:58 by iidzim            #+#    #+#             */
/*   Updated: 2021/05/22 11:26:36 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_token	*init_token(e_token_type type, char *s)
{
	t_token	*t;

	// printf("f:init_token\t[%s]\n", c);
	t = malloc(sizeof(t_token));
	if (!t)
		return (NULL);
	t->value = ft_strdup(s);
	t->type = type;
	return (t);
}

t_lexer *init_lexer(char *line)
{
	t_lexer *l;

	l = malloc(sizeof(t_lexer));
	if (!l)
		return (NULL);
	l->buffer = ft_strdup(line);
	l->bufsize = ft_strlen(line);
	l->c = ' ';
	l->curpos = 0;
	l->readpos = 0;
	return (l);
}

t_lexer *read_cmd()
{
	size_t r;
	char *line;
	char *buffer;

	buffer = malloc(sizeof(char) * 2);
	r = read(0, buffer, 1);
	line = malloc(sizeof(char) * 2); 
	if (!buffer || !line)
		return(NULL);
	line[0] = '\0';
	while( r > 0)
	{
		buffer[1] = 0;
		if (buffer[0] == '\n')
			break ;
		line = ft_strjoinchar(line, buffer[0]);
		r = read(0, buffer, 1);
	}
	free(buffer);
	return(init_lexer(line));
}

int	valid_envar(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*envar_token(t_lexer *l)
{
	char	*str;
	char	*temp;

	if (!l)
		return (NULL);
	str = ft_strdup("");
	readchar(l);
	if (ft_isdigit(l->c))
	{
		if (l->c == '0')
			str = ft_strjoin(str, "minishell");
		readchar(l);
		return (tokenize_text(l, str));
	}
	while (valid_envar(l->c) && l->c != EOF)
	{
		temp = str;
		str = ft_strjoinchar(str, l->c);
		readchar(l);
		free(temp);
	}
	str = getenv(str);
	if (!str)
		str = ft_strdup("");
	return (str);
}
