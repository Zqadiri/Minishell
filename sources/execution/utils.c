/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 15:31:05 by zqadiri           #+#    #+#             */
/*   Updated: 2021/09/01 14:46:00 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count(t_cmd *cmd, t_token_type type)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cmd->redir_nbr)
	{
		if (cmd->r[i].type == type)
			j++;
		i++;
	}
	return (j);
}

int	len(char **env)
{
	register int	len;

	len = 0;
	while (env[len])
		len++;
	return (len);
}

int	ft_strlen_new(const char *str)
{
	int		len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

int	alpha(char *key)
{
	int	i;

	i = 0;
	while (key[i] != '\0')
	{
		if (ft_isalpha(key[i]))
			i++;
		else
			return (-1);
	}
	return (1);
}

char	*get_env_var_by_key(char *key)
{
	int		index;
	char	*value;
	int		i;

	value = NULL;
	index = 0;
	i = 0;
	if (!key)
		return (NULL);
	index = find_env(key);
	if (index == -1)
		return (NULL);
	value = return_value(g_global->env_var[index], '=');
	return (value);
}
