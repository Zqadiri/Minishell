/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 11:00:28 by iidzim            #+#    #+#             */
/*   Updated: 2021/09/19 18:53:38 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_envar(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*ft_getenv(char *str)
{
	char	**env_var;
	char	*value;
	char	*temp;
	int		i;

	value = ft_strdup("");
	i = -1;
	while (g_global->env_var[++i])
	{
		env_var = ft_split(g_global->env_var[i], '=');
		if (!ft_strcmp(env_var[0], str))
		{
			temp = value;
			value = ft_strdup(env_var[1]);
			free(temp);
			ft_freeptr(env_var[0]);
			ft_freeptr(env_var[1]);
			ft_freeptr(env_var);
			break ;
		}
		ft_freeptr(env_var[0]);
		ft_freeptr(env_var[1]);
		ft_freeptr(env_var);
	}
	return (value);
}

char	*string_envar(t_lexer *l)
{
	char	*str;

	if (ft_isdigit(l->c))
	{
		readchar(l);
		str = ft_strdup("");
		while (l->c != EOF && !ft_strchar("|><\"\' $", l->c))
		{
			str = ft_joinchar(str, l->c);
			readchar(l);
		}
	}
	else
	{
		str = ft_strdup("$");
		while (l->c != EOF && !ft_strchar("|><\"\'$", l->c))
		{
			str = ft_joinchar(str, l->c);
			readchar(l);
		}
	}
	return (str);
}

char	*invalid_envar(t_lexer *l, int i)
{
	char	*str;
	char	*s;

	if (i == 1)
	{
		if (l->c == '0')
			str = ft_strdup("minishell");
		else if (l->c == '?')
			str = ft_itoa(g_global->exit_status);
		else
			return (string_envar(l));
		readchar(l);
		s = tokenize_text(l, str);
		free(str);
		return (s);
	}
	else
	{
		str = ft_strdup("a");
		str[0] = l->c;
		readchar(l);
		return (str);
	}
}

char	*envar_token(t_lexer *l)
{
	char	*str;
	char	*v;

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
	v = ft_getenv(str);
	free(str);
	if (!v)
		return (NULL);
	return (v);
}
