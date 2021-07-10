/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:28:30 by iidzim            #+#    #+#             */
/*   Updated: 2021/07/10 21:34:03 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <errno.h>
# include "./exec.h"
# include "lexer.h"
# include "parser.h"
# include <readline/readline.h>
# include <readline/history.h>

// t_lexer	*read_cmd(void);

/*
** History
*/

typedef struct s_global
{
	char	**env_var;
	int		exit_status;
}	t_global;

t_global	*g_global;

typedef struct s_red
{
	int		*infile_fds;
	int		*outfile_fds;
	int		less_cpt;
	int		great_cpt;
	int		greater_cpt;
}	t_red;

// typedef struct s_data
// {
// 	char	**path;
// }	t_data;


t_lexer	*history(void);
void	move_up(t_index *m, t_lexer *l);
void	move_down(t_index *m, t_lexer *l);

#endif
