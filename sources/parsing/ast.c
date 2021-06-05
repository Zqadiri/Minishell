/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:47:46 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/05 17:03:52 by iidzim           ###   ########.fr       */
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
	ast->comp_values = (void*) 0;
	ast->comp_size = 0;
	ast->pipecmd_values = (void*) 0;
	ast->pipecmd_size = 0;
	ast->args = 0;
	ast->args_size = 0;
	return (ast);
}

void	visitor(t_ast *ast)
{
	int	i;
	int	j;
	int	k;

	if (!ast)
		return ;
	if (ast->type == compound)
	{
		i = -1;
		printf("f:visitor compound size = [%d]\n", ast->comp_size);
		while (++i < ast->comp_size)
		{
			visitor(ast->comp_values[i]);
			if (ast->comp_size >= 2)
				// printf("f:visitor\ttoken -> [;][semi]\n");
				printf(";;;;;;;;;;;;;;\n");
		}
	}
	if (ast->type == pipe_ast)
	{
		j = -1;
		printf("f:visitor pipe size = [%d]\n", ast->pipecmd_size);
		while (++j < ast->pipecmd_size)
		{
			visitor(ast->pipecmd_values[j]);
			if (ast->pipecmd_size >= 2)
				// printf("f:visitor\ttoken -> [|][pipe]\n");
				printf("||||||||||||||\n");
		}
	}
	if (ast->type == arg_ast)
	{
		k = -1;
		printf("f:visitor args size = [%d]\n", ast->args_size);
		while (++k < ast->args_size)
			printf("f:visitor\ttoken -> [%s][%u]\n", ast->args[k]->value,
				ast->args[k]->type);
	}
}

void	is_notempty(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

t_ast	*free_pip_args(t_ast *ast)
{
	int	k;

	if (ast->type == arg_ast)
	{
		k = -1;
		while (++k < ast->args_size)
		{
			is_notempty(ast->args[k]->value);
			is_notempty(ast->args[k]);
		}
		is_notempty(ast->args);
	}
	return (NULL);
}

t_ast	*free_tree(t_ast *ast)
{
	int	i;
	int	j;

	if (ast->type == compound)
	{
		i = -1;
		while (++i < ast->comp_size)
		{
			if (ast->comp_values[i])
				free_tree(ast->comp_values[i]);
		}
		is_notempty(ast->comp_values);
	}
	if (ast->type == pipe_ast)
	{
		j = -1;
		while (++j < ast->pipecmd_size)
		{
			if (ast->pipecmd_values[j])
				free_tree(ast->pipecmd_values[j]);
		}
		is_notempty(ast->pipecmd_values);
	}
	return (free_pip_args(ast));
}
