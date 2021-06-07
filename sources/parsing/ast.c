/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:47:46 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/07 16:01:49 by iidzim           ###   ########.fr       */
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
	ast->comp_values = (void*) 0;
	ast->comp_size = 0;
	ast->pipecmd_values = (void*) 0;
	ast->pipecmd_size = 0;
	ast->args = 0;
	ast->args_size = 0;
	return (ast);
}

void	print_tree(t_ast *ast)
{
	int	i;
	int	j;
	int	k;

	if (!ast)
		return ;
	if (ast->type == compound)
	{
		i = -1;
		printf("f:print_tree compound size = [%d]\n", ast->comp_size);
		while (++i < ast->comp_size)
		{
			print_tree(ast->comp_values[i]);
			if (ast->comp_size >= 2)
				printf("f:print_tree\ttoken -> [;][semi]\n");
		}
	}
	if (ast->type == pipe_ast)
	{
		j = -1;
		printf("f:print_tree pipe size = [%d]\n", ast->pipecmd_size);
		while (++j < ast->pipecmd_size)
		{
			print_tree(ast->pipecmd_values[j]);
			if (ast->pipecmd_size >= 2)
				printf("f:print_tree\ttoken -> [|][pipe]\n");
		}
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

t_cmd	*visitor(t_ast *ast)
{
	t_cmd *z;
	int		i;
	int		j;
	int		k;
	int		l;
	int		m;
	int		n;

	if (!ast)
		return (NULL);
	n = 0;
	if (ast->type == compound)
	{
		i = -1;
		while (++i < ast->comp_size)
		{
			printf("f:visitor\tcheck compound size = [%d]\n", ast->comp_size);
			z = visitor(ast->comp_values[i]);
			z[n].type = semi;
			if (ast->comp_size >= 2)
				printf("f:visitor\ttoken -> [;][semi]\n");
		}
	}
	if (ast->type == pipe_ast)
	{
		j = -1;
		while (++j <= ast->pipecmd_size)
		{
			printf("f:visitor\tcheck pipe size = [%d]\n", ast->pipecmd_size);
			z = visitor(ast->pipecmd_values[j]);
			z[n].type = pip;
			if (ast->pipecmd_size >= 2)
				printf("f:visitor\ttoken -> [|][pipe]\n");
			n++;
		}
	}
	l = 0;
	m = 0;
	if (ast->type == arg_ast)
	{
		k = 0;
		printf("f:visitor\targs size = [%d]\n", ast->args_size);
		z[n].argvs = malloc(sizeof(char*) * ast->args_size);
		while (k < ast->args_size)
		{
			if (!is_redirection((ast->args[k])))
			{
				z[n].argvs[l] = ft_strdup(ast->args[k]->value);
				printf("f:visitor\targument num [%d] >> [%s]\n", l, z[n].argvs[l]);
				l++;
				k++;
			}
			else
			{
				k += 1;
				if (is_redirection(ast->args[k - 1]) && k >= 1)
				{
					printf("f:visitor\t [%s] is redirection \n", ast->args[k - 1]->value);
					z[n].r[m].type = ast->args[k - 1]->type;
					z[n].r[m].filename = ast->args[k]->value;
					m++;
				}
				k++;
			}
		}
		printf(">>>>>>>>>>> [%s]\n", z[n].argvs[l]);
	}
	return (z);
}

void	print_cmd(t_cmd *z)
{
	int i;
	int j;

	//print redirection struct
	i = -1;
	while (z->r[++i].type)
		printf("f:printzineb\t redirection %d = [%s][%u]\n", i, z->r[i].filename, z->r[i].type);
	//print args
	j = -1;
	while (z->argvs[++j])
		printf("f:printzineb\t arg %d = [%s]\n", j, z->argvs[j]);
	printf("f:printzineb\t type = [%u]\n", z->type);
}
