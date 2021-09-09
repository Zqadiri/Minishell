/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:27:47 by iidzim            #+#    #+#             */
/*   Updated: 2021/09/09 16:51:24 by zqadiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*init_l(t_lexer	*l)
{
	l = malloc(sizeof(t_lexer));
	if (!l)
		return (NULL);
	l->buffer = NULL;
	l->bufsize = 0;
	l->c = ' ';
	l->curpos = 0;
	l->readpos = 0;
	return (l);
}

void	initialize(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	g_global = malloc(sizeof(t_global));
	if (g_global == NULL)
		exit(EXIT_FAILURE);
	dup_env_var(env);
	g_global->exit_status = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
}

void	quit_minishell(void)
{
	char		*cm_cap;
	char		*up;
	char		*ri;

	up = tgetstr("up", NULL);
	ri = tgetstr("RI", NULL);
	cm_cap = tgetstr("cm", NULL);
	tputs(ri, 1, putchar);
	tputs(ri, 1, putchar);
	tputs(ri, 1, putchar);
	tputs(up, 1, putchar);
	printf("exit\n");
	g_global->exit_status = 0;
	exit(g_global->exit_status);
}

void	parse(t_lexer *l)
{
	t_cmd		*z;
	t_ast		*ast;
	t_parser	*p;

	p = init_parser(l);
	if (p)
	{
		ast = parse_pipe(p);
		if (ast)
		{
			z = visitor(ast);
			if (z)
			{
				execution(z);
				free_cmd(z);
			}
		}
	}
	if (p)
		free(p);
}

int	main(int argc, char **argv, char **env)
{
	t_lexer		*l;
	char		*buff;

	initialize(argc, argv, env);
	while (1)
	{
		buff = NULL;
		buff = readline("minishell$> ");
		if (!buff)
			quit_minishell();
		else if (buff[0] == '\0')
		{
			free(buff);
			system("leaks minishell");
			continue;
		}
		else
		{
			l = NULL;
			l = init_l(l);
			add_history(buff);
			if (!is_white_space(buff))
			{
				l->buffer = ft_strdup(buff);
				l->bufsize = ft_strlen(l->buffer);
			}
			free (buff);
		}
		parse(l);
		system("leaks minishell");
	}
	return (0);
}

// ! heap-buffer-overflow get_stop_word parser_utils.c:62 > cat << eof
// ! < Makefile <<'EOF' |  sed 's/l/e/g'