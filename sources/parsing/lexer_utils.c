/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 11:00:28 by iidzim            #+#    #+#             */
/*   Updated: 2021/07/10 19:35:06 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	readchar(t_lexer *l)
{
	if (!l || !l->buffer)
		printf("error\n");
	if (l->readpos >= l->bufsize)
		l->c = EOF;
	else
		l->c = l->buffer[l->readpos];
	l->curpos = l->readpos;
	l->readpos++;
}

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

char	*invalid_envar(t_lexer *l, char *str)
{
	char	*temp;

	temp = str;
	if (l->c == '0')
	{
		str = ft_strjoin(str, "minishell");
		free(temp);
	}
	if (l->c == '?')
	{
		str = ft_strjoin(str, ft_itoa(g_global->exit_status));
		free(temp);
	}
	readchar(l);
	return (tokenize_text(l, str));
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
			printf("str = [%s]\n", value);
			free(temp);
			break ;
		}
		else
			i++;
	}
	return (value);
}

char	*envar_token(t_lexer *l)
{
	char	*str;
	char	*temp;

	if (!l)
		return (NULL);
	str = ft_strdup("");
	readchar(l);
	if (ft_isdigit(l->c) || l->c == '?')
		return (invalid_envar(l, str));
	while (valid_envar(l->c) && l->c != EOF)
	{
		temp = str;
		str = ft_joinchar(str, l->c);
		readchar(l);
		free(temp);
	}
	str = ft_getenv(g_global->env_var, str);
	if (!str)
		str = ft_strdup("");
	return (str);
}
