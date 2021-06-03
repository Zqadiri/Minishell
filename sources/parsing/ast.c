/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:47:46 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/03 15:51:22 by iidzim           ###   ########.fr       */
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
	//AST_ARG
	ast->args = 0;
	ast->args_size = 0;
	return (ast);
}

void visitor(t_ast *ast)
{
	int i, j, k;

	if (ast->type == compound)
	{
		i = -1;
		while (++i < ast->comp_size)
			visitor(ast->comp_values[i]);
	}
	if (ast->type == pipe_ast)
	{
		j = -1;
		while (++j < ast->pipecmd_size)
			visitor(ast->pipecmd_values[j]);
			
	}
	if (ast->type == arg_ast)
	{
		k = -1;
		while (++k < ast->args_size)
			printf("f:visitor\ttoken -> [%s][%u]\n", ast->args[k]->value,
				ast->args[k]->type);
	}
}