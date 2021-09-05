/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 20:17:30 by iidzim            #+#    #+#             */
/*   Updated: 2021/09/06 00:12:26 by mac              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	is_notempty(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_tree(t_ast *ast)
{
	int	j;
	int	k;

	if (ast->type == pipe_ast)
	{
		j = -1;
		while (++j < ast->pipecmd_size)
		{
			if (ast->pipecmd_values[j])
				free_tree(ast->pipecmd_values[j]);
		}
		free(ast->pipecmd_values);
	}
	if (ast->type == arg_ast)
	{
		k = -1;
		while (++k < ast->args_size)
		{
			is_notempty(ast->args[k]->value);
			is_notempty(ast->args[k]);
		}
		free(ast->args);
	}
	free(ast);
}

void	free_tree2(t_ast **ast)
{
	int	i;
	int	j;

	j = -1;
	while (++j < (*ast)->pipecmd_size)
	{
		i = -1;
		while (++i < ast[j]->pipecmd_size)
		{
			if (ast[j]->pipecmd_values[i])
				free_tree(ast[j]->pipecmd_values[i]);
		}
		is_notempty(ast[j]);
	}
	is_notempty(ast);
}

void	free_parser(t_parser *p)
{
	if (p->lexer)
	{
		is_notempty(p->lexer->buffer);
		free(p->lexer);
		p->lexer = NULL;
	}
	free(p);
	p = NULL;
}

void	free_parser2(t_parser *p)
{
	if (p->lexer)
	{
		is_notempty(p->lexer->buffer);
		free(p->lexer);
		p->lexer = NULL;
	}
	if (p->prev_token)
	{
		is_notempty(p->prev_token->value);
		free(p->prev_token);
		p->prev_token = NULL;
	}
	if (p->curr_token)
	{
		is_notempty(p->curr_token->value);
		free(p->curr_token);
		p->curr_token = NULL;
	}
	free(p);
	p = NULL;
}

void	free_cmd(t_cmd *z)
{
	int	i;
	// int	j;

	i = -1;
	// j = -1;
	// while (z[++j].argvs)
	// {
		// while (z[j].argvs[++i])
			// is_notempty(z[j].argvs[i]);
	// }
	while (z->argvs[++i])
		is_notempty(z->argvs[i]);
	is_notempty(z->r);
	free(z->argvs);
	// while (z[++i].argvs)
	// 	is_notempty(z[i].argvs);
	// while (z[++i].r)
	// 	is_notempty(z[i].r);
	free(z);
}
