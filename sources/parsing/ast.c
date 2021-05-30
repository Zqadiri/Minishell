/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:47:46 by iidzim            #+#    #+#             */
/*   Updated: 2021/05/30 19:45:42 by iidzim           ###   ########.fr       */
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

// ! t5erbi9
// void print_tree(t_ast *ast)
// {
// 	int i, j, k, l;

// 	i = j = k = l = 0;
// 	printf("f:print_tree\n");
// 	printf("f:print_tree\t comp_size = %d \n", ast->comp_size);
// 	printf("f:print_tree\t pipe_size = %d \n", ast->pipecmd_size);
// 	printf("f:print_tree\t cmd_size = %d \n", ast->simplecmd_size);
// 	printf("f:print_tree\t args_size = %d \n", ast->args_size);

// 	while (i < ast->comp_size)
// 	{
// 		while (j < ast->comp_values[i]->pipecmd_size)
// 		{
// 			while (k < ast->comp_values[i]->pipecmd_values[ast->comp_values[i]->pipecmd_size]->pipecmd_size)
// 			{
// 				while (l < ast->comp_values[i]->pipecmd_values[ast->comp_values[i]->pipecmd_size]->args[])
// 				{
// 					printf("token->value --> [%s]\n", ast->args[ast->args_size]->value);
// 					printf("token->value --> [%u]\n", ast->args[ast->args_size]->type);
// 					l--;
// 				}
// 				k--;
// 			}
// 			j--;
// 		}
// 		i--;
// 	}
// 	return ;
// }