/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:55:09 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/03 15:14:22 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast   *parse_compound(t_parser *p)
{
	t_ast	*ast;
	t_ast	*ast_semi;
	char	*str;

	if (!p)
		return (NULL);
	str = ft_strdup("");
	while (p->curr_token->type != eof)
	{
		ast = parse_pipe(p, &str);
		if (!ast)
			return (NULL);
		ast_semi = init_ast(compound);
		ast_semi->comp_values = (t_ast**)malloc(sizeof(t_ast*));
		if (!)
		
	}
	return (ast);
}