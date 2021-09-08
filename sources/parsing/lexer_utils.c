/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 11:00:28 by iidzim            #+#    #+#             */
/*   Updated: 2021/09/08 16:59:39 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	peek_char(t_lexer *l)
{
	if (l->readpos >= l->bufsize)
		return (EOF);
	else
		return (l->buffer[l->readpos]);
}

int	valid_envar(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*ft_getenv(char **env, char *str)
{
	char	**env_var;
	char	*value;
	char	*temp;
	int		i;

	i = 0;
	value = ft_strdup("");
	while (env[i])
	{
		env_var = ft_split(env[i], '=');
		if (!ft_strcmp(env_var[0], str))
		{
			temp = value;
			value = ft_strdup(env_var[1]);
			free(temp);
			break ;
		}
		else
			i++;
	}
	return (value);
}

// char	*invalid_envar(t_lexer *l, char *str, int i)//*
// {
// 	char	*temp;

// 	if (i == 1)
// 	{
// 		temp = str;
// 		if (l->c == '0')
// 		{
// 			str = ft_strjoin(str, "minishell");
// 			free(temp);
// 		}
// 		if (l->c == '?')
// 			str = ft_joinfree(str, ft_itoa(g_global->exit_status));
// 		readchar(l);
// 		return (tokenize_text(l, str));
// 	}
// 	else
// 	{
// 		str = ft_joinchar(str, l->c);
// 		readchar(l);
// 		return (str);
// 	}
// }

char	*invalid_envar(t_lexer *l, int i)
{
	char	*str;

	if (i == 1)
	{
		if (l->c == '0')
			str = ft_strdup("minishell");
		if (l->c == '?')
			str = ft_itoa(g_global->exit_status);
		readchar(l);
		return (tokenize_text(l, str));
	}
	else
	{
		str = ft_strdup("a");
		str[0] = l->c;
		readchar(l);
		return (str);
	}
}

// char	*envar_token(t_lexer *l)//*
// {
// 	char	*str;

// 	if (!l)
// 		return (NULL);
// 	str = ft_strdup("");
// 	if (peek_char(l) == '$' || peek_char(l) == '\"' || peek_char(l) == '\''
// 		|| peek_char(l) == EOF)
// 		return (invalid_envar(l, str, 0));
// 	readchar(l);
// 	if (ft_isdigit(l->c) || l->c == '?' || !valid_envar(l->c))
// 		return (invalid_envar(l, str, 1));
// 	while (valid_envar(l->c) && l->c != EOF)
// 	{
// 		str = ft_joinchar(str, l->c);
// 		readchar(l);
// 	}
// 	str = ft_getenv(g_global->env_var, str);
// 	if (!str)
// 		return (ft_strdup(""));
// 	return (str);
// }

char	*envar_token(t_lexer *l)
{
	char	*str;

	if (!l)
		return (NULL);
	if (peek_char(l) == '$' || peek_char(l) == '\"' || peek_char(l) == '\''
		|| peek_char(l) == EOF)
		return (invalid_envar(l, 0));
	readchar(l);
	if (ft_isdigit(l->c) || l->c == '?' || !valid_envar(l->c))
		return (invalid_envar(l, 1));
	str = ft_strdup("");
	while (valid_envar(l->c) && l->c != EOF)
	{
		str = ft_joinchar(str, l->c);
		readchar(l);
	}
	str = ft_getenv(g_global->env_var, str);
	if (!str)
		return (NULL);
	return (str);
}