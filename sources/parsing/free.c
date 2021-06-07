/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 20:17:30 by iidzim            #+#    #+#             */
/*   Updated: 2021/06/06 20:18:54 by iidzim           ###   ########.fr       */
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

void	free_parser(t_parser *p)
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
}
