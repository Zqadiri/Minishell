/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:47:46 by iidzim            #+#    #+#             */
/*   Updated: 2021/05/25 12:51:20 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*init_ast(e_ast_type type)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->type = type;
	//AST_COMPOUND
	ast->comp_values = (void*) 0;
	ast->comp_size = 0;
	//AST_PIPE
	ast->pipecmd_values = (void*) 0;
	ast->pipecmd_size = 0;
	//AST_CMD
	ast->simplecmd_values = (void*) 0;
	ast->simplecmd_size = 0;
	//AST_ARG
	ast->args = 0;
	ast->args_size = 0;
	return (ast);
}
