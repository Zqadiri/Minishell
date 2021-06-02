/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:47:46 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/02 14:13:48 by iidzim           ###   ########.fr       */
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
	// //AST_CMD
	// ast->simplecmd_values = (void*) 0;
	// ast->simplecmd_size = 0;
	//AST_ARG
	ast->args = 0;
	ast->args_size = 0;
	return (ast);
}

// void print_ast(t_ast *ast)
// {
// 	int cmd_semi = 0;
// 	int cmd_pipe;
// 	int cmd_args;
// 	t_ast *temp, temp1, temp2, temp3;

// 	while (cmd_semi < ast->comp_size)
// 	{
// 		temp = ast->comp_values[cmd_semi];
// 		temp1 = temp->pipecmd_values[0];
// 		temp2 = temp1
// 		printf("ast -> %s\n", temp->);
// 		cmd_semi++;
// 	}
// 	printf("end loop\n");
// }  

// t_ast *visitor(t_ast ast)
// {
// }