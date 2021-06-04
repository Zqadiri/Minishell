/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:47:46 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/04 17:03:33 by iidzim           ###   ########.fr       */
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

	if (!ast)
		return ;
	if (ast->type == compound)
	{
		i = -1;
		printf("f:visitor compound size = [%d]\n",ast->comp_size);
		while (++i < ast->comp_size)
		{
			visitor(ast->comp_values[i]);
			if (ast->comp_size >= 2)
				printf("f:visitor\ttoken -> [;][semi]\n");
		}
	}
	if (ast->type == pipe_ast)
	{
		j = -1;
		printf("f:visitor pipe size = [%d]\n",ast->pipecmd_size);
		while (++j < ast->pipecmd_size)
		{
			visitor(ast->pipecmd_values[j]);
			if (ast->pipecmd_size >= 2)
				printf("f:visitor\ttoken -> [|][pipe]\n");
		}
	}
	if (ast->type == arg_ast)
	{
		k = -1;
		printf("f:visitor args size = [%d]\n",ast->args_size);
		while (++k < ast->args_size)
			printf("f:visitor\ttoken -> [%s][%u]\n", ast->args[k]->value,
				ast->args[k]->type);
	}
}

t_ast	*free_tree(t_ast *ast)
{
	int i, j, k;

	if (ast->type == compound)
	{
		i = -1;
		while (++i < ast->comp_size)
		{
			if (ast->comp_values[i])
				free_tree(ast->comp_values[i]);
		}
		if (ast->comp_values)
		{
			free(ast->comp_values);
			ast->comp_values = NULL;
		}
	}
	if (ast->type == pipe_ast)
	{
		j = -1;
		while (++j < ast->pipecmd_size)
		{
			if (ast->pipecmd_values[j])
				free_tree(ast->pipecmd_values[j]);
		}
		if (ast->pipecmd_values)
		{
			free(ast->pipecmd_values);
			ast->pipecmd_values = NULL;
		}
	}
	if (ast->type == arg_ast)
	{
		k = -1;
		while (++k < ast->args_size)
		{
			if (ast->args[k]->value)
			{
				free(ast->args[k]->value);
				ast->args[k]->value = NULL;
			}
			if (ast->args[k])
			{
				free(ast->args[k]);
				ast->args[k] = NULL;
			}
		}
		if (ast->args)
		{
			free(ast->args);
			ast->args = NULL;
		}
	}
	return (NULL);
}