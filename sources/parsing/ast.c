/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:47:46 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/28 15:36:14 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*init_ast(t_ast_type type)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->type = type;
	ast->pipecmd_values = (void *) 0;
	ast->pipecmd_size = 0;
	ast->args = 0;
	ast->redir_nbr = 0;
	ast->args_size = 0;
	return (ast);
}

void	print_tree(t_ast *ast)
{
	int	j;
	int	k;

	if (!ast)
		return ;
	if (ast->type == pipe_ast)
	{
		j = -1;
		printf("f:print_tree pipe size = [%d]\n", ast->pipecmd_size);
		while (++j < ast->pipecmd_size)
			print_tree(ast->pipecmd_values[j]);
	}
	if (ast->type == arg_ast)
	{
		k = -1;
		printf("f:print_tree args size = [%d]\n", ast->args_size);
		while (++k < ast->args_size)
			printf("f:print_tree\ttoken -> [%s][%u]\n", ast->args[k]->value,
				ast->args[k]->type);
	}
}

t_cmd	*visitor_args(t_ast *ast, t_cmd *z, int n)
{
	int	k;
	int	l;
	int	m;

	l = 0;
	m = 0;
	if (ast->type == arg_ast)
	{
		k = 0;
		// printf("f:visitor\targs size = [%d]\n", ast->args_size);
		// printf("f:visitor\tredirection nbr = [%d]\n\n", ast->redir_nbr);
		z[n].argvs = malloc(sizeof(char *) * (ast->args_size + 1));
		z[n].r = malloc(sizeof(t_redir) * ast->redir_nbr);
		z[n].redir_nbr = ast->redir_nbr;
		z[n].args_size = ast->args_size - (z[n].redir_nbr * 2) - 1;
		printf("***f:visitor\targs size = [%d]\n", z[n].args_size);
		printf("***f:visitor\tredirection nbr = [%d]\n", z[n].redir_nbr);
		while (k < ast->args_size && (ast->args[k]->type != eof
				|| ast->args[k]->type != pip))
		{
			if (ast->args[k]->type == id)
			{
				z[n].argvs[l] = ft_strdup(ast->args[k]->value);
				printf("f:visitor\targument num [%d] >> [%s]\n",
					l, z[n].argvs[l]);
				l++;
				k++;
			}
			else
			{
				k += 1;
				if (is_redirection(ast->args[k - 1]) && k >= 1
					&& m < ast->redir_nbr)
				{
					printf("f:visitor\t type -> [%s]\n", ast->args[k - 1]->value);
					printf("f:visitor\t filename -> [%s]\n", ast->args[k]->value);
					z[n].r[m].type = ast->args[k - 1]->type;
					z[n].r[m].filename = ast->args[k]->value;
					m++;
				}
				k++;
			}
		}
		z[n].argvs[l] = NULL;
	}
	return (z);
}

t_cmd	*visitor(t_ast *ast)
{
	t_cmd	*z;
	int		j;
	int		n;

	if (!ast)
		return (NULL);
	n = 0;
	if (ast->type == pipe_ast)
	{
		j = -1;
		while (++j < ast->pipecmd_size)
		{
			printf("f:visitor\tcheck pipe size = [%d]\n", ast->pipecmd_size);
			z = visitor(ast->pipecmd_values[j]);
			if (ast->pipecmd_size >= 2)
				z[n].type = pip;
			n++;
		}
	}
	if (ast->type == arg_ast)
		z = visitor_args(ast, z, n);
	return (z);
}
