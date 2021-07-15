/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:38:32 by iidzim            #+#    #+#             */
/*   Updated: 2021/07/13 12:40:47 by iidzim           ###   ########.fr       */
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

char	*invalid_envar_here_doc(char *buff, int i, char *str)
{
	char	*temp;

	temp = str;
	if (buff[i] == '0')
	{
		str = ft_strjoin(str, "minishell");
		free(temp);
	}
	if (buff[i] == '?')
	{
		str = ft_strjoin(str, ft_itoa(g_global->exit_status));
		free(temp);
	}
	return (str);
}

char	*envar_here_doc(char *buff, int i)
{
	char	*str;
	char	*temp;

	str = ft_strdup("");
	if (ft_isdigit(buff[i]) || buff[i] == '?')
		return (invalid_envar_here_doc(buff, i, str));
	while (valid_envar(buff[i]) && buff[i] != EOF)
	{
		temp = str;
		str = ft_joinchar(str, buff[i]);
		free(temp);
		i++;
	}
	str = ft_getenv(g_global->env_var, str);
	if (!str)
		str = ft_strdup("");
	return (str);
}

void	parse_here_doc(t_redir *r)
{
	char	*buff;
	char	*str;
	char	*temp;
	int		i;
	int		fd;

	if (r->type == here_doc && r->is_quoted == 0)
	{
		fd = open("/temp/heredoc", O_RDONLY | O_WRONLY | O_CREAT | O_APPEND);
		if (fd < -1)
			return ;// ! error while opening the file
		while (1)
		{	
			buff = readline("> ");
			if (!ft_strcmp(buff, r->filename) || !buff)
				break ;
			str = ft_strdup("");
			i = -1;
			while (buff[++i] != '\0')
			{
				temp = str;
				if (buff[i] == DOLLAR)
					str = ft_strjoin(str, envar_token_here_doc(buff, i + 1));
				else
					str = ft_joinchar(str, buff[i]);
				free(temp);
			}
			ft_putendl_fd(str, fd);
		}
	}
}
