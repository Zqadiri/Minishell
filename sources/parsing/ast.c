/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:47:46 by iidzim            #+#    #+#             */
/*   Updated: 2021/09/06 18:35:35 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_ast(t_ast *ast, t_ast_type type)
{
	ast->type = type;
	ast->pipecmd_values = (void *) 0;
	ast->pipecmd_size = 0;
	ast->args = 0;
	ast->redir_nbr = 0;
	ast->args_size = 0;
}

void	init_cmdargs(t_ast *ast, t_cmd *z, int n)
{
	z[n].redir_nbr = ast->redir_nbr;
	z[n].args_size = ast->args_size - (z[n].redir_nbr * 2) - 1;
	z[n].r = malloc(sizeof(t_redir) * ast->redir_nbr);
	if (z[n].args_size > 0)
		z[n].argvs = malloc(sizeof(char *) * (z[n].args_size + 1));
}

void	visitor_args(t_ast *ast, t_cmd *z, int n)
{
	t_index	x;

	x = (t_index){.k = 0, .l = 0, .m = 0};
	init_cmdargs(ast, z, n);
	while (x.k < ast->args_size && (ast->args[x.k]->type != eof
			|| ast->args[x.k]->type != pip))
	{
		if (ast->args[x.k]->type == id)
		{
			z[n].argvs[x.l++] = ft_strdup(ast->args[x.k++]->value);
			printf("args[%d] = [%s]\n", x.l - 1, z[n].argvs[x.l - 1]);
		}
		else
		{
			if (is_redic(ast->args[++x.k - 1]) && x.k >= 1
				&& x.m < ast->redir_nbr)
			{
				z[n].r[x.m].type = ast->args[x.k - 1]->type;
				z[n].r[x.m].is_quoted = ast->args[x.k]->is_quoted;
				z[n].r[x.m++].filename = ast->args[x.k++]->value;
				printf("[%s] - [%u]\n", z[n].r[x.m - 1].filename, z[n].r[x.m - 1].type);
			}
		}
	}
	z[n].argvs[x.l] = NULL;
}

void	init_cmd(t_cmd z)
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

	z = malloc(sizeof(t_cmd) * (ast->pipecmd_size + 1));
	if (!z)
		return (NULL);
	n = 0;
	z->nbr_cmd = ast->pipecmd_size;
	if (ast->type == pipe_ast)
	{
		j = -1;
		while (++j < ast->pipecmd_size && n <= z->nbr_cmd)
		{
			init_cmd(z[n]);
			visitor_args(ast->pipecmd_values[j], z, n);
			if (ast->pipecmd_size >= 2 && j < ast->pipecmd_size - 1)
				z[n].type = pip;
			else
				z[n].type = eof;
			n++;
		}
	}
	free_tree(ast);
	return (z);
}
