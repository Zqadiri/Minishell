/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 20:17:30 by iidzim            #+#    #+#             */
/*   Updated: 2021/09/07 19:13:50 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	is_notempty(void **ptr)
{
	char *s;

	s = (char *)(*ptr);
	if (s)
	{
		free(s);
		*ptr = NULL;
	}
}

void	free_tree(t_ast **astt)
{
	int	j;
	int	k;

	t_ast *ast;
	ast = *astt;
	if (!ast)
		return ;
	printf("%u\n", ast->type);
	if (ast->type == pipe_ast)
	{
		j = -1;
		while (++j < ast->pipecmd_size)
		{
			if (ast->pipecmd_values[j])
			{
				free_tree(&(ast->pipecmd_values[j]));
			}
		}
		free(ast->pipecmd_values);
	}
	if (ast->type == arg_ast)
	{
		k = -1;
		while (++k < ast->args_size)
		{
			printf("%d %d\n", ast->args_size, k);
			if (ast->args[k])
			{
				printf("**1 %s\n", ast->args[k]->value);
				is_notempty((void **)(ast->args[k]->value));
			}
			is_notempty((void **)&(ast->args[k]));
			// if (ast->args[k])
			// {
			// 	free(ast->args[k]);
			// 	ast->args[k] = NULL;
			// }
			printf("here\n");
		}
		free(ast->args);
	}
	free(ast);
	*astt = NULL;
}

void	free_tree2(t_ast **ast)
{
	int	i;
	int	j;

	j = -1;
	if (!(*ast) || !ast)
		return ;
	while (++j < (*ast)->pipecmd_size)
	{
		i = -1;
		while (++i < ast[j]->pipecmd_size)
		{
			if (ast[j]->pipecmd_values[i])
				free_tree(&(ast[j]->pipecmd_values[i]));
		}
		is_notempty((void **)ast[j]);
	}
	is_notempty((void **)ast);
}

void	free_tree3(t_token **token, int size)
{
	int j;

	j = -1;
	while (++j < size - 1)
	{
		printf("**2\n");
		is_notempty((void **)(token[j]->value));
	}
	is_notempty((void **)token);
}

void	free_parser(t_parser **pp)
{
	t_parser *p;

	p = *pp;
	if (!p)
		return ;
	if (p->lexer)
	{
		is_notempty((void **)(p->lexer->buffer));
		free(p->lexer);
		p->lexer = NULL;
	}
	free(p);
	*pp = NULL;
}

void	free_parser2(t_parser **pp)
{
	t_parser *p;

	p = *pp;
	if (!p)
		return ;
	if (p->lexer)
	{
		is_notempty((void **)(p->lexer->buffer));
		free(p->lexer);
		p->lexer = NULL;
	}
	if (p->prev_token)
	{
		printf("**3\n");
		is_notempty((void **)(p->prev_token->value));
		free(p->prev_token);
		p->prev_token = NULL;
	}
	if (p->curr_token)
	{
		printf("**4\n");
		is_notempty((void **)(p->curr_token->value));
		free(p->curr_token);
		p->curr_token = NULL;
	}
	free(p);
	*pp = NULL;
}

void	free_cmd(t_cmd *z)
{
	// int j;

	// // i = 0;
	// // while (z[i].nbr_cmd < i)
	// // {
	// 	j = 0;
	// 	while (j < z->args_size)
	// 	{
	// 		printf("innn\n");
	// 		free(z->argvs[j]);
	// 		z->argvs[j] = NULL;
	// 		j++;
	// 	}
	// 	free(z->argvs);
	// 	z->argvs = NULL;
	// 	j = 0;
	// 	while (j < z->redir_nbr)
	// 	{
	// 		free(z->r[j].filename);
	// 		z->r[j].filename = NULL;
	// 		j++;
	// 	}
	// 	free(z->r);
	// 	z->r = NULL;
	// 	// i++;
	// // }

	int i;
	int j;

	if (!z)
		return ;
	i = -1;
	while (++i < z->nbr_cmd)
	{
		j = -1;
		while (++j < z[i].args_size)
			is_notempty((void **)(z[i].argvs[j]));
		free(z[i].argvs);
		j = -1;
		while (++j < z[i].redir_nbr)
			is_notempty((void **)(z[i].r[j].filename));
		free(z[i].r);
	}
	free(z);
}
