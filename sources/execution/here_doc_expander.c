/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:05:12 by iidzim            #+#    #+#             */
/*   Updated: 2021/09/24 13:05:34 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*invalid_envar_here_doc(char *buff, int i)
{
	char	*s;

	s = ft_strdup("");
	if (buff[i] == '?')
		s = ft_joinfree(s, ft_itoa(g_global->exit_status));
	else
	{
		i += 1;
		while (buff[i] != '\0' && buff[i] != 32)
		{
			s = ft_joinchar(s, buff[i]);
			i++;
		}
	}
	return (s);
}

char	*envar_here_doc(char *buff, int i)
{
	char	*s;
	char	*env;
	char	*temp;

	if (!ft_strcmp(buff, "\0") || i == 1)
	{
		s = ft_strdup(buff);
		return (s);
	}
	i = -1;
	s = ft_strdup("");
	while (buff[++i] != '\0')
	{
		if (buff[i] != DOLLAR)
			s = ft_joinchar(s, buff[i]);
		else
		{
			i += 1;
			if (ft_isdigit(buff[i]) || buff[i] == '?')
			{
				temp = invalid_envar_here_doc(buff, i);
				i += ft_strlen(temp);
				s = ft_joinfree(s, temp);
			}	
			else
			{
				env = ft_strdup("");
				while (buff[i] != '\0' && valid_envar(buff[i]))
				{
					env = ft_joinchar(env, buff[i]);
					i++;
				}
				s = ft_joinfree(s, ft_getenv(env));
				free(env);
				s = ft_joinchar(s, buff[i]);
			}
		}
	}
	return (s);
}
