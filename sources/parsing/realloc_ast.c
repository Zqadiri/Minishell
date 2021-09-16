/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 16:15:34 by iidzim            #+#    #+#             */
/*   Updated: 2021/09/16 16:00:55 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	**realloc_ast_node(t_ast *ast, int size)
{
	t_ast	**new;
	int		i;

	if (ast->type == pipe_ast)
	{
		new = (t_ast **)malloc(sizeof(t_ast *) * size);
		i = -1;
		while (++i < ast->pipecmd_size)
			new[i] = ast->pipecmd_values[i];
		new[i] = NULL;
		free(ast->pipecmd_values);
		ast->pipecmd_values = NULL;
		return (new);
	}
	return (NULL);
}

t_token	**realloc_ast_args(t_ast *ast, int size)
{
	t_token	**new;
	int		i;

	if (ast->type == arg_ast)
	{
		new = (t_token **)malloc(sizeof(t_token *) * (size + 1));
		i = -1;
		while (++i < size - 1)
			new[i] = ast->args[i];
		new[i] = NULL;
		free(ast->args);
		ast->args = NULL;
		return (new);
	}
	return (NULL);
}

void	print_msg(char *str, char *var)
{
	printf("%s", str);
	if (var)
	{
		printf(" `");
		printf("%s", var);
		printf("'\n");
	}
	g_global->exit_status = 258;
}

char	*tokenize_text(t_lexer *l, char *s)
{
	char	*str;

	str = ft_strdup(s);
	while (l->c != EOF && !ft_strchar("|>< \"\'", l->c))
	{
		while (l->c == 32 && l->c != EOF)
			readchar(l);
		if (l->c == DOLLAR)
			str = ft_joinfree(str, envar_token(l));
		else if (l->c == EOF)
			return (str);
		else
		{
			str = ft_joinchar(str, l->c);
			readchar(l);
		}
	}
	return (str);
}

void	ft_freeptr(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

char	*string_envar(t_lexer *l)
{
	char	*str;

	str = ft_strdup("$");
	while (l->c != EOF && !ft_strchar("|><\"\'", l->c))
	{
		str = ft_joinchar(str, l->c);
		readchar(l);
	}
	return (str);
}
