/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:37:40 by iidzim            #+#    #+#             */
/*   Updated: 2021/05/04 12:35:55 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parser *init_parser(t_lexer *l)
{
    t_parser *p;
    
    if (!l)
        return (NULL);
    printf("ok\n");
    p = malloc(sizeof(t_parser));
    if (!p)
        return (NULL);
    p->lexer = l;
    p->curr_token = get_next_token(l);
    p->prev_token = p->curr_token;
    return (p);
}

// ToDo:
// expectPeek() : primary purpose is to enforce the correctness of the order
// of tokens by checking the type of the next token.
