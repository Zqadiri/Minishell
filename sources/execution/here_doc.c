/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:38:32 by iidzim            #+#    #+#             */
/*   Updated: 2021/09/24 17:25:00 by iidzim           ###   ########.fr       */
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

char	*herdoc_helper(char *buff, char *output, char *filename, int is_quoted)
{
	char	*temp;

	if (!ft_strcmp(buff, filename))
	{
		free(buff);
		return (NULL);
	}
	if (ft_strcmp(output, "\0"))
	{
		temp = output;
		output = ft_strjoin(output, "\n");
		free(temp);
	}
	output = ft_joinfree(output, envar_here_doc(buff, is_quoted));
	free(buff);
	return (output);
}

void	parse_here_doc(t_redir *r, t_data *m)
{
	char	*buff;
	char	*output;
	char	*temp;
	int		fd;

	m->redir->filename_ = random_file_name();
	fd = open(m->redir->filename_, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0) //!!! exit after display msg
		check_valid_fd(m, m->redir->filename_, fd);
	output = ft_strdup("");
	while (1)
	{
		m->redir->in_heredoc = 1;
		buff = readline("> ");
		temp = output;
		output = herdoc_helper(buff, output, r->filename, r->is_quoted);
		if (!output)
			break ;
	}
	ft_putendl_fd(temp, fd);
	free(output);
	free(temp);
	close (fd);
}

//? 1 leak -> free filename -struct redir- + norm