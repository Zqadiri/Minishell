/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:27:47 by iidzim            #+#    #+#             */
/*   Updated: 2021/09/06 18:56:28 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_tree(t_ast *ast)
{
	int	j;
	int	k;

	if (!ast)
		return ;
	// printf("ast->type = [%u]\n", ast->type);
	if (ast->type == pipe_ast)
	{
		j = -1;
		// printf("f:print_tree pipe size = [%d]\n", ast->pipecmd_size);
		while (++j < ast->pipecmd_size)
		{
			// printf("next type => [%u]\n", ast->pipecmd_values[j]->type);
			print_tree(ast->pipecmd_values[j]);
		}
	}
	if (ast->type == arg_ast)
	{
		k = -1;
		printf("f:print_tree args size = [%d]\n", ast->args_size);
		while (++k < ast->args_size)
		{
			printf("f:print_tree\ttoken -> [%s][%u]\n", ast->args[k]->value,
				ast->args[k]->type);
		}
	}
}

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
	// signal(SIGTERM, terminate_process);
	return (l);
}

int	is_white_space(char *buff)
{
	int	i;

	i = 0;
	while (buff[i] == 32 || buff[i] == '\t')
		i++;
	if (buff[i] == '\0')
		return (1);
	return (0);
}


int main(int argc, char **argv, char **env)
{
	t_lexer		*l;
	t_parser	*p;
	t_ast		*ast;
	t_cmd 		*z;
	char		*buff;

	(void)argc;
	(void)argv;
	g_global = malloc(sizeof(t_global));
	if (g_global == NULL)
		return (EXIT_FAILURE);
	dup_env_var(env);
	g_global->exit_status = 0;
	signal(SIGINT, sigint_handler);
	// signal(SIGQUIT, sigint_handler);
	while(1)
	{
		l = NULL;
		l = init_l(l);
		buff = NULL;
		buff = readline("minishell$> ");
		if (!buff)
		{
			char *cm_cap = tgetstr("left", NULL);
			tputs(tgoto(cm_cap , 0, 0), 0, putchar);
			char *cm_cap2 = tgetstr("left", NULL);
			tputs(tgoto(cm_cap2 , 0, 0), 0, putchar);
			printf("exit\n");
			exit(g_global->exit_status);
		}
		else //if (ft_strcmp(buff, "\0"))
		{
			add_history(buff);
			if (!is_white_space(buff))
			{
				l->buffer = ft_strdup(buff);
				l->bufsize = ft_strlen(l->buffer);
			}
			free (buff);
		}
		// else
		// 	continue;
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
		// system("leaks minishell");
	}
	return (0);
}

// ToDo List:
//? << stp
//? << stp cat
//? << 'stp' cat
//? << st'p' cat
//? << st'p cat
//? << $PWD cat
// example :							 output
//* √- echo c'o\'u'cou'					-> co\ucou 
//* √- ec"ho" bon"'j'o'u"r				-> bon'j'o'ur
//* √- ec"ho" bon"j'o\'u"r				-> bonj'o\'ur
//* √- echo co'c"o"u'					-> coc"o"u
//* √- echo co'"c\"o"u'					-> co"c\"o"u
//* √- ec"ho" bon"jo"u"r					-> add " f next line ->bonjour
//* √- ec"ho" bon"jo\"u"r					-> bonjo"ur
//* √- echo bo'njou\$r					-> add ' f next line ->bonjou\$r
//* √- echo bo"njou\$r					-> add " f next line ->bonjou$r
//* √- ec"ho" bon"jo\"u"r					-> bonjo"ur
//* √- echo "\\"							-> \
//* √- bash-3.2$ echo A B C
//* >>A B C
//* √- bash-3.2$ echo A''B''C
//* >>ABC
//* - bash-3.2$ echo A '' B '' C
//* >>A  B  C
//* - bash-3.2$ echo A  B  C
//* >>A B C
//* bash-3.2$ export number="0 1  2       3"
//* bash-3.2$ env | less
//* bash-3.2$ echo "$number"
//* 0 1  2       3
//* bash-3.2$ echo $number - trim environment variable
//* 0 1 2 3
//* -> $IFS default separators used for field splitting 
// ! switch cmd name to lowercase before cmp




//* stty -echoctl


//! Leaks : 
//! cmd with pipeline 
//! syntax error 
//? xthxrtj || trjrs
