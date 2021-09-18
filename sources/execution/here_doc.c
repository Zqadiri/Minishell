/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:38:32 by iidzim            #+#    #+#             */
/*   Updated: 2021/09/18 11:59:40 by zqadiri          ###   ########.fr       */
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
	str = ft_getenv(str);
	if (!str)
		str = ft_strdup("");
	return (str);
}

char	*random_file_name(void)
{
	static int	file_nbr = 0;
	char		*name;
	char		*itoa_nbr;

	file_nbr++;
	name = NULL;
	itoa_nbr = ft_itoa(file_nbr);
	name = ft_strjoin("/tmp/file", itoa_nbr);
	free(itoa_nbr);
	return (name);
}

void	parse_here_doc(t_redir *r, t_data *m)
{
	char	*buff;
	char	*output;
	int		fd;

	output = ft_strdup("");
	m->redir->filename_ = random_file_name();
	fd = open(m->redir->filename_, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		check_valid_fd(m, m->redir->filename_, fd);
	while (1)
	{
		m->redir->in_heredoc = 1;
		buff = readline("> ");
		if (!ft_strcmp(buff, r->filename))
			break ;
		else
		{
			output = ft_strjoin(output, buff);
			output = ft_strjoin(output, "\n");
		}
	}
	ft_putendl_fd(output, fd);
	close (fd);
}
