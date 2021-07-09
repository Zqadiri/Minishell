/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:38:32 by iidzim            #+#    #+#             */
/*   Updated: 2021/07/09 21:48:56 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*to_lower(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] >= 65 && s[i] <= 90)
			s[i] += 32;
		i++;
	}
	return (s);
}

int	mixte(t_cmd	*z)
{
	int		i;
	char	*s;

	if (!z)
		return (NULL);
	i = -1;
	while (z[++i].argvs)
	{
		s = to_lower(z[i].argvs[0]);
		if (is_builtin(s))
			exec_cmd(z);
		else if (is_cmdpath(s))
			exec_cmd(z);
		else
		{
			printf("minishell: %s: command not found\n", z[i].argvs[0]);
			return (0);
		}
	}
	return (1);
}

char	*exit_status(char *s, int index)
{
	char	*temp;
	char	*ret_value;

	ret_value = ft_substr(s, 0, index);
	temp = ret_value;
	ret_value = ft_strjoin(ret_value, get_return_value());
	free(temp);
	return (ret_value);
}

// char    *expander(t_cmd *cmd)
// {
//     int i;

//     i = -1;
//     while (++i < cmd->args_size)
//     {
//         if (ft_strnstr(cmd->argvs[i], "$?", 2))
//     }
// }

//!
/*
char	*tokenize_dquoted_text(t_lexer *l)
{
	char	*str;
	char	*temp;

	readchar(l);
	if (l->c == EOF)
		if (!multi_lines(l, DQUOTE))
			return (NULL);
	str = ft_strdup("");
	while (l->c != DQUOTE && l->c != EOF)
	{
		temp = str;
		// check_string(l, str, 1);
		if (l->c == DOLLAR)
			str = ft_strjoin(str, envar_token(l));
		else
		{
			str = ft_strjoinchar(str, l->c);
			readchar(l);
		}
		free(temp);
	}
	if (!multi_lines(l, DQUOTE))
		return (NULL);
	readchar(l);
	return (str);
}

char	*tokenize_squoted_text(t_lexer *l)
{
	char	*str;
	char	*temp;
	int		s;

	s = 0;
	readchar(l);
	str = ft_strdup("");
	while (l->c != SQUOTE && l->c != EOF)
	{
		temp = str;
		str = ft_strjoinchar(str, l->c);
		readchar(l);
		free(temp);
	}
	if (l->c == SQUOTE)
		s += 1;
	if (l->c == EOF && s == 0)
		if (!multi_lines(l, SQUOTE))
			return (NULL);
	readchar(l);
	return (str);
}

t_token	*string_token(t_lexer *l)
{
	char	*str;
	char	*temp;
	char	*s;

	str = ft_strdup("");
	while (l->curpos <= l->bufsize && l->c != PIPE && l->c != GREAT
		&& l->c != LESS && l->c != EOF)
	{
		temp = str;
		if (l->c == DQUOTE)
		{
			s = tokenize_dquoted_text(l);
			if (!s && l->multi_line == 1)
			{
				printf("error>>>\n");
				return (ret_str(l, NULL, illegal));
			}
			str = ft_strjoin(str, s);
			free(s);
		}
		else if (l->c == SQUOTE)
		{
			s = tokenize_squoted_text(l);
			if (!s && l->multi_line == 1)
				return (ret_str(l, NULL, illegal));
			str = ft_strjoin(str, s);
			free(s);
		}
		else
			str = ft_strjoin(str, tokenize_text(l, NULL));
		free(temp);
		if (l->c == 32)
			return (ret_str(l, str, id));
	}
	return (ret_str(l, str, id));
}
*/