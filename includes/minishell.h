/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:28:30 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/06 20:59:59 by iidzim           ###   ########.fr       */
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

# define PATH_MAX 15000




// t_lexer	*read_cmd(void);

/*
** History
*/

t_lexer	*history(void);
void	move_up(t_index *m, t_lexer *l);
void	move_down(t_index *m, t_lexer *l);

#endif
