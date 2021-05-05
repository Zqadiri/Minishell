/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:37:40 by iidzim            #+#    #+#             */
/*   Updated: 2021/05/05 14:56:14 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parser *init_parser(t_lexer *l)
{
    t_parser *p;
    
    if (!l)
        return (NULL);
    p = malloc(sizeof(t_parser));
    if (!p)
        return (NULL);
    p->lexer = l;
    p->curr_token = get_next_token(l);
    p->prev_token = p->curr_token;
    printf("current token -> %s\n", p->curr_token->value);
	printf("previous token -> %s\n\n", p->prev_token->value);
    return (p);
}

t_ast *parse_stat()
{
    
}

t_ast *parse_statements(t_parser *p)
{
    t_ast *ast;

    ast = init_ast(compound);
    ast->comp_values = (t_ast**)malloc(sizeof(t_ast*));
    if (!ast->comp_values)
        return (NULL);
    ast->comp_values[0] = parse_stat(p);
    ast->comp_size++;
    //recursive
    //while()
    {
        
    }
}

// ToDo:
// expectPeek() : primary purpose is to enforce the correctness of the order
// of tokens by checking the type of the next token.

