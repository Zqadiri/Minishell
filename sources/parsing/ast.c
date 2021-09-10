/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:47:46 by iidzim            #+#    #+#             */
/*   Updated: 2021/09/10 12:19:10 by iidzim           ###   ########.fr       */
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
	if ((ast->args_size - 1) == (ast->redir_nbr * 2))
		z[n].argvs = NULL;
	while (x.k < ast->args_size - 1 && (ast->args[x.k]->type != eof
			|| ast->args[x.k]->type != pip))
	{
		if (ast->args[x.k]->type == id)
			z[n].argvs[x.l++] = ft_strdup(ast->args[x.k++]->value);
		else
		{
			if (is_redic(ast->args[++x.k - 1]) && x.k >= 1
				&& x.m < ast->redir_nbr)
			{
				z[n].r[x.m].type = ast->args[x.k - 1]->type;
				z[n].r[x.m].is_quoted = ast->args[x.k]->is_quoted;
				z[n].r[x.m++].filename = ft_strdup(ast->args[x.k++]->value);
			}
		}
	}
	if (x.l != 0)
		z[n].argvs[x.l] = NULL;
}

void	init_cmd(t_cmd z)
{
	z.args_size = 0;
	z.argvs = NULL;
	z.redir_nbr = 0;
	z.r = NULL;
}

// void	print_cmd(t_cmd *z, int n)
// {
// 	int	i;
// 	int	j;

// 	(void)n;
// 	i = -1;
// 	while (++i < z[0].nbr_cmd)
// 	{
// 		j = -1;
// 		while (z[i].args_size > ++j)
// 			printf("cmd[%d].args[%d] = [%s]\n", i, j, z[i].argvs[j]);
// 		j = -1;
// 		while (z[i].redir_nbr > ++j)
// 		{
// 			printf("cmd[%d].file[%d] = [%s] - ", i, j, z[i].r[j].filename);
// 			printf("cmd[%d].type[%d] = [%u]\n", i, j, z[i].r[j].type);
// 		}
// 	}
// }

t_cmd	*visitor(t_ast *ast)
{
	t_cmd	*z;
	t_index	x;

	x = (t_index){.k = 0, .l = -1, .m = -1};
	z = malloc(sizeof(t_cmd) * (ast->pipecmd_size + 1));
	if (!z)
		return (NULL);
	if (ast->type == pipe_ast)
	{
		while (++(x.l) < ast->pipecmd_size && x.k < ast->pipecmd_size)
		{
			init_cmd(z[x.k]);
			visitor_args(ast->pipecmd_values[x.l], z, x.k);
			if (ast->pipecmd_size >= 2 && x.l < ast->pipecmd_size - 1)
				z[x.k].type = pip;
			else
				z[x.k].type = eof;
			(x.k)++;
		}
		x.m = -1;
		while (++(x.m) < x.k)
			z[x.m].nbr_cmd = x.k;
	}
	free_tree(ast);
	return (z);
}
