/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 11:13:01 by iidzim            #+#    #+#             */
/*   Updated: 2021/07/12 12:36:08 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include "../libft/libft.h"

# define PIPE 124
# define GREAT 62
# define GREATER 63 //">>"
# define LESS 60
// # define LESS 60
# define DQUOTE 34
# define SQUOTE 39
# define SPACE 32
# define DOLLAR 36
# define BSLASH 92
# define TILDE 126

typedef enum e_token_type
{
	pip,
	great,
	greater,
	less,
	here_doc,
	id,
	illegal,
	eof
}			t_token_type;

// ! 2 60 100 100
// ! 1     
/*
** lexer->buffer		: the input text
** lexer->bufsize		: size of the input text
** lexer->curpos		: absolute char position in source
** lexer->readpos		: after current pos
** lexer->c				: current char under examination
** lexer->multi_line	: is true --> multiple_lines
*/

typedef struct s_lexer
{
	char	*buffer;
	int		bufsize;
	int		curpos;
	int		readpos;
	char	c;
	int		multi_line;
	int		is_quoted;
}				t_lexer;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				is_quoted;
}				t_token;

/*
** get_next_token.c
*/
char	*tokenize_text(t_lexer *l, char *s);
t_token	*string_token(t_lexer *l);

/*
** lexer.c
*/
void	readchar(t_lexer *l);
t_token	*ret_str(t_lexer *l, char *s, int type);
t_token	*get_next_token(t_lexer *l);


/*
** lexer_utlis.c
*/
int		peek_char(t_lexer *l);
char	*envar_token(t_lexer *l);

/*
** utils.c
*/
t_token	*init_token(t_token_type type, char *s, t_lexer *l);
int		ftstrcmp(char *s1, char *s2);
char	*ft_joinchar(char *s, char c);
int		is_valid_id(char *str);

#endif
