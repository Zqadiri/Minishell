/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:38:32 by iidzim            #+#    #+#             */
/*   Updated: 2021/09/13 16:15:16 by zqadiri          ###   ########.fr       */
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
	str = ft_getenv(g_global->env_var, str);
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

	(void)r;
	output = ft_strdup("");
	if (m->redir->filename_ != NULL)
	{
		unlink(m->redir->filename_);
		free (m->redir->filename_);
		m->redir->filename_ = NULL;
	}
	else
		m->redir->filename_ = random_file_name();
	fd = open(m->redir->filename_, O_RDONLY | O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		check_valid_fd(m, m->redir->filename_, fd);
	m->redir->infile = fd;
	while (1)
	{
		m->redir->in_heredoc = 1;
		buff = readline("> ");
		// printf ("buff %s\n", buff); 
		if (ft_strcmp(buff, "exit"))
			break ;
		else
		{
			output = ft_strdup("");
			output = ft_strjoin(output, buff);
			ft_putendl_fd(output, fd);
		}
		m->redir->in_heredoc = 0;
	}
	printf("output : %s\n", output);
	ft_putendl_fd(output, fd);
	// printf("out");
}

// void	parse_here_doc(t_redir *r, t_data *m)
// {
// 	char	*buff;
// 	char	*str;
// 	char	*temp;
// 	int		i;
// 	int		fd;

// 	if (r->type == here_doc /*&& r->is_quoted == 0*/)
// 	{
// 		if (m->redir->filename_ != NULL)
// 		{
// 			unlink(m->redir->filename_);
// 			free (m->redir->filename_);
// 			m->redir->filename_ = NULL;
// 		}
// 		m->redir->filename_ = random_file_name();
// 		fd = open(m->redir->filename_, O_RDONLY|O_WRONLY|O_CREAT, 0644);
// 		if (fd < 0)
// 			check_valid_fd(m, m->redir->filename_, fd);
// 		while (1)
// 		{
// 			m->redir->in_heredoc = 1;
// 			buff = readline("> ");
// 			if (!ft_strcmp(buff, r->filename))
// 			{
// 				printf ("here !\n");
// 				break;
// 			}
// 			str = ft_strdup("");
// 			i = -1;
// 			while (buff[++i] != '\0')
// 			{
// 				temp = str;
// 				if (buff[i] == DOLLAR)
// 					str = ft_strjoin(str, envar_here_doc(buff, i + 1));
// 				else
// 					str = ft_joinchar(str, buff[i]);
// 			}
// 			m->redir->in_heredoc = 0;
// 		}
// 		ft_putendl_fd(str, fd);
// 		printf ("out");
// 	}
// }
