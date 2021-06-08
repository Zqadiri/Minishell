/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:47:46 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/08 19:37:12 by iidzim           ###   ########.fr       */
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
	//
	ast->comp_values = (void*) 0;
	ast->comp_size = 0;
	//
	ast->pipecmd_values = (void*) 0;
	ast->pipecmd_size = 0;
	//
	ast->args = 0;
	ast->redir_nbr = 0;
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
	printf("f:print\ttype = [%u]\n", ast->type);
	if (ast->type == compound)
	{
		i = -1;
		printf("f:print_tree compound size = [%d]\n", ast->comp_size);
		while (++i < ast->comp_size)
		{
			print_tree(ast->comp_values[i]);
			// if (ast->comp_size >= 2)
				// printf("f:print_tree\ttoken -> [;][semi]\n");
		}
	}
	if (ast->type == pipe_ast)
	{
		j = -1;
		printf("f:print_tree pipe size = [%d]\n", ast->pipecmd_size);
		while (++j < ast->pipecmd_size)
		{
			print_tree(ast->pipecmd_values[j]);
			// if (ast->pipecmd_size >= 2)
				// printf("f:print_tree\ttoken -> [|][pipe]\n");
		}
	}
	if (ast->type == arg_ast)
	{
		k = -1;
		printf("f:print_tree args size = [%d]\n", ast->args_size);
		while (++k < ast->args_size)// && ast->args[k]->type != eof)
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
		printf("f:visitor\targs size = [%d]\n", ast->args_size);
		printf("f:visitor\tredirection nbr = [%d]\n", ast->redir_nbr);
		z[n].argvs = malloc(sizeof(char*) * ast->args_size);
		z[n].r = malloc(sizeof(t_redir) * ast->redir_nbr);
		while (k < ast->args_size && (ast->args[k]->type != eof || ast->args[k]->type != pip || ast->args[k]->type != semi))
		{
			// printf("f:visitor\t k = [%d]\n", k);
			if (ast->args[k]->type == id)
			{
				z[n].argvs[l] = ft_strdup(ast->args[k]->value);
				printf("f:visitor\targument num [%d] >> [%s]\n", l, z[n].argvs[l]);
				l++;
				k++;
			}
			else
			{
				k += 1;
				if (is_redirection(ast->args[k - 1]) && k >= 1 && m < ast->redir_nbr)
				{
					printf("f:visitor\t [%s] \n", ast->args[k - 1]->value);
					printf("f:visitor\t [%s] -> filename \n", ast->args[k]->value);
					// printf("f:visitor\t n = [%d] m = [%d]\n", n, m);
					z[n].r[m].type = ast->args[k - 1]->type;
					z[n].r[m].filename = ast->args[k]->value;
					m++;
				}
				k++;
			}
			// printf("f:visitor\t n = [%d] | type = [%u]\n", n, z[n].type);
		}
	}
	return (z);
}

t_cmd	*visitor(t_ast *ast)
{
	t_cmd	*z;
	int		i;
	int		j;
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
			if (ast->comp_size >= 2)
			{
				z[n].type = semi;
				printf("f:visitor\t n = [%d] | type = [%u]\n", n, z[n].type);
			}
			n++;
		}
	}
	if (ast->type == pipe_ast)
	{
		j = -1;
		while (++j < ast->pipecmd_size)
		{
			printf("f:visitor\tcheck pipe size = [%d]\n", ast->pipecmd_size);
			z = visitor(ast->pipecmd_values[j]);
			if (ast->pipecmd_size >= 2)
			{
				z[n].type = pip;
				printf("f:visitor\t n = [%d] | type = [%u]\n", n, z[n].type);
			}
			n++;
		}
	}
	if (ast->type == arg_ast)
		z = visitor_args(ast, z, n);
	return (z);
}

// void ft_nizar_realloc(void **chi, int size, int nb)
// {
// 	void *new;

// 	new = malloc(size * nb);
	
// }