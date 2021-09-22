/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:38:32 by iidzim            #+#    #+#             */
/*   Updated: 2021/09/22 11:30:33 by zqadiri          ###   ########.fr       */
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

// char	*invalid_envar_here_doc(char *buff, int i, char *str)
// {
// 	char	*temp;

// 	temp = str;
// 	if (buff[i] == '0')
// 	{
// 		str = ft_strjoin(str, "minishell");
// 		free(temp);
// 	}
// 	if (buff[i] == '?')
// 	{
// 		str = ft_strjoin(str, ft_itoa(g_global->exit_status));
// 		free(temp);
// 	}
// 	return (str);
// }

// char	*envar_here_doc(char *buff, int i)
// {
// 	char	*str;
// 	char	*temp;

// 	str = ft_strdup("");
// 	if (ft_isdigit(buff[i]) || buff[i] == '?')
// 		return (invalid_envar_here_doc(buff, i, str));
// 	while (valid_envar(buff[i]) && buff[i] != EOF)
// 	{
// 		temp = str;
// 		str = ft_joinchar(str, buff[i]);
// 		free(temp);
// 		i++;
// 	}
// 	str = ft_getenv(str);
// 	if (!str)
// 		str = ft_strdup("");
// 	return (str);
// }

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
		return (buff);
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
	printf ("here !\n");
	char	*buff;
	char	*output;
	char	*temp;
	int		fd;

	m->redir->filename_ = random_file_name();
	fd = open(m->redir->filename_, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		check_valid_fd(m, m->redir->filename_, fd); //!!! exit after display msg 
	output = ft_strdup("");
	while (1)
	{
		m->redir->in_heredoc = 1;
		buff = readline("> ");
		if (!ft_strcmp(buff, r->filename))
		{
			free(buff);
			break ;
		}
		else
		{
			output = ft_joinfree(output, envar_here_doc(buff, r->is_quoted));
			temp = output;
			output = ft_strjoin(output, "\n");
			free(temp);
		}
		free(buff);
	}
	ft_putendl_fd(output, fd);
	free(output);
	close (fd);
}

//? 1 leak -> free filename -struct redir- + norm
