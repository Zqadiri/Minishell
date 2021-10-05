/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:27:47 by iidzim            #+#    #+#             */
/*   Updated: 2021/10/05 12:32:13 by zqadiri          ###   ########.fr       */
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

char	**get_env_(char	**env_)
{
	char	**env;
	int		i;

	i = -1;
	env = (char **)malloc(sizeof(char *) * (len(env_) + 1));
	if (env == NULL)
		exit(EXIT_FAILURE);
	while (++i < len(env_))
		env[i] = ft_strdup(env_[i]);
	env[i] = 0;
	return (env);
}

void	initialize(int argc, char **argv, char **env, t_state *state)
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
	state->env_ = get_env_(env);
	state->path = get_path();
}

void	quit_minishell(void)
{
	char		*up;
	char		*ri;

	up = tgetstr("up", NULL);
	ri = tgetstr("RI", NULL);
	tputs(ri, 1, putchar);
	tputs(ri, 1, putchar);
	tputs(ri, 1, putchar);
	tputs(up, 1, putchar);
	printf("exit\n");
	exit(g_global->exit_status);
}

void	parse(t_lexer *l, t_state *state)
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
				execution(z, state);
				if (z)
					free_cmd(z);
			}
		}
	}
	if (p)
		free(p);
}

void test(char **buff, t_lexer **l)
{
	add_history(*buff);
	if (!is_white_space(*buff))
	{
		(*l) = init_l(*l);
		(*l)->buffer = ft_strdup(*buff);
		(*l)->bufsize = ft_strlen((*l)->buffer);
	}
	free (*buff);
}

int	main(int argc, char **argv, char **env)
{
	t_lexer		*l;
	char		*buff;
	t_state		*state;

	state = (t_state *)malloc(sizeof(t_state));
	initialize(argc, argv, env, state);
	while (1)
	{
		buff = NULL;
		buff = readline("minishell$> ");
		if (!buff)
			quit_minishell();
		else if (buff[0] == '\0')
		{
			free(buff);
			continue ;
		}
		else
		{
			l = NULL;
			test(&buff, &l);
		}
		parse(l, state);
	}
	return (0);
}
