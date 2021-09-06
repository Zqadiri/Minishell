/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 20:17:30 by iidzim            #+#    #+#             */
/*   Updated: 2021/09/06 18:46:55 by iidzim           ###   ########.fr       */
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

void	free_tree3(t_token **token, int size)
{
	int j;

	j = -1;
	while (++j < size - 1)
		is_notempty(token[j]->value);
	is_notempty(token);
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
	int j;

	i = 0;
	while (i < z[i].nbr_cmd)
	{
		j = 0;
		while (j < z[i].args_size)
		{
			free(z[i].argvs[j]);
			z[i].argvs[j] = NULL;
			j++;
		}
		free(z[i].argvs);
		j = 0;
		while (j < z[i].redir_nbr)
		{
			free(z[i].r[j].filename);
			z[i].r[j].filename = NULL;
			j++;
		}
		free(z[i].r);
	}
	free(z);
}
