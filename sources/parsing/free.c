/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 20:17:30 by iidzim            #+#    #+#             */
/*   Updated: 2021/09/09 15:41:50 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tree(t_ast *ast)
{
	int	j;
	int	k;

	if (!ast)
		return ;
	if (ast->type == pipe_ast)
	{
		j = -1;
		while (++j < ast->pipecmd_size)
		{
			if (ast->pipecmd_values[j])
			{
				free_tree((ast->pipecmd_values[j]));
				ast->pipecmd_values[j] = NULL;
				printf("here2\n");
			}
		}
		free(ast->pipecmd_values);
	}
	if (ast->type == arg_ast)
	{
		k = 0;
		while (k < ast->args_size)
		{
			// printf("size = %d -- k = %d\n", ast->args_size, k);
			if (ast->args[k])
			{
				if(ast->args[k]->value)
					free(ast->args[k]->value);
				ast->args[k]->value = NULL;
			}
			if(ast->args[k])
				free(ast->args[k]);
			ast->args[k] = NULL;
			k++;
		}
		free(ast->args);
	}
	free(ast);
	//?ast = NULL;//
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
			{
				free_tree((ast[j]->pipecmd_values[i]));
				ast[j]->pipecmd_values[i] = NULL;
			}
		}
		free(ast[j]);
		ast[j] = NULL;
	}
	free(*ast);
	*ast = NULL;
}

void	free_parser(t_parser *p)
{
	if (!p)
		return ;
	if (p->lexer)
	{
		// is_notempty((void **)(p->lexer->buffer));
		if (p->lexer->buffer)
			free(p->lexer->buffer);
		p->lexer->buffer = NULL;
		free(p->lexer);
		p->lexer = NULL;
	}
}

void	free_parser2(t_parser *p)
{

	if (!p)
		return ;
	if (p->lexer)
	{
		if(p->lexer->buffer)
			free(p->lexer->buffer);
		p->lexer->buffer = NULL;
		free(p->lexer);
		p->lexer = NULL;
	}
	if (p->prev_token)
	{
		printf("**3\n");
		if(p->prev_token->value)
			free(p->prev_token->value);
		p->prev_token->value = NULL;
		free(p->prev_token);
		p->prev_token = NULL;
	}
	if (p->curr_token)
	{
		printf("**4\n");
		if(p->curr_token->value)
			free(p->curr_token->value);
		p->curr_token->value = NULL;
		free(p->curr_token);
		p->curr_token = NULL;
	}
	free(p);
}

void	free_parser3(t_parser *p)
{

	if (!p)
		return ;
	if (p->lexer)
	{
		if(p->lexer->buffer)
			free(p->lexer->buffer);
		p->lexer->buffer = NULL;
		free(p->lexer);
		p->lexer = NULL;
	}
	if (p->curr_token)
	{
		printf("**4\n");
		if(p->curr_token->value)
			free(p->curr_token->value);
		p->curr_token->value = NULL;
		free(p->curr_token);
		p->curr_token = NULL;
	}
}

void	free_cmd(t_cmd *z)
{
	int i;
	int j;

	if (!z)
		return ;
	i = -1;
	while (++i < z->nbr_cmd)
	{
		j = -1;
		while (++j < z[i].args_size)
		{
			if(z[i].argvs[j])
				free(z[i].argvs[j]);
			z[i].argvs[j] = NULL;
		}
		free(z[i].argvs);
		j = -1;
		while (++j < z[i].redir_nbr)
		{
			if(z[i].r[j].filename)
				free(z[i].r[j].filename);
			z[i].r[j].filename = NULL;
		}
		free(z[i].r);
	}
	free(z);
}
