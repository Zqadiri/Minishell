/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:47:46 by iidzim            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/07/10 13:16:35 by iidzim           ###   ########.fr       */
=======
/*   Updated: 2021/07/10 12:46:51 by zqadiri          ###   ########.fr       */
>>>>>>> 5e6eca20353cec6c67e99e8a7c390c5ec26ac121
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

void	init_cmd(t_ast *ast, t_cmd *z, int n)
{
	z[n].redir_nbr = ast->redir_nbr;
	z[n].args_size = ast->args_size - (z[n].redir_nbr * 2) - 1;
	z[n].argvs = malloc(sizeof(char *) * (z[n].args_size + 1));
	z[n].r = malloc(sizeof(t_redir) * ast->redir_nbr);
}

t_cmd	*visitor_args(t_ast *ast, t_cmd *z, int n)
{
	int	k;
	int	l;
	int	m;

	l = 0;
	m = 0;
	k = 0;
	init_cmd(ast, z, n);
	while (k < ast->args_size && (ast->args[k]->type != eof
			|| ast->args[k]->type != pip))
	{
		if (ast->args[k]->type == id)
		{
			z[n].argvs[l++] = ft_strdup(ast->args[k++]->value);
			printf("args[%d] = [%s]\n", l - 1, z[n].argvs[l - 1]);
		}
		else
		{
			if (is_redic(ast->args[++k - 1]) && k >= 1 && m < ast->redir_nbr)
			{
				z[n].r[m].type = ast->args[k - 1]->type;
				z[n].r[m++].filename = ast->args[k++]->value;
				printf("[%s] - [%u]\n", z[n].r[m - 1].filename, z[n].r[m - 1].type);
			}
		}
		// printf("f:visitor_args\tpipe**** ==> [%u]\n", z[n].redir_nbr);
	}
	// printf("f:visitor_args\tpipe-------- ==> [%u]\n", z[n].redir_nbr);
	z[n].argvs[l] = NULL;
	return (z);
}

void	inittt(t_cmd z)
{
	z.args_size = 0;
	z.argvs = NULL;
	z.redir_nbr = 0;
	z.r = NULL;
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
		printf("pipe size = %d\n", ast->pipecmd_size);
		while (++j < ast->pipecmd_size)
		{
			inittt(z[n]);
			z = visitor(ast->pipecmd_values[j]);
			if (ast->pipecmd_size >= 2 && j < ast->pipecmd_size - 1)
			{
				z[n].type = pip;
				printf("type = [%u]\n", z[n].type);
			}
			else
			{
				z[n].type = eof;
				printf("type = [%u]\n", z[n].type);
			}
			printf("f:visitor\t****type = [%u]\n", z[n].type);
			n++;
		}
	}
	if (ast->type == arg_ast)
		z = visitor_args(ast, z, n);
	return (z);
}
