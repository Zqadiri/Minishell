/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:38:32 by iidzim            #+#    #+#             */
/*   Updated: 2021/07/10 17:32:49 by zqadiri          ###   ########.fr       */
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
