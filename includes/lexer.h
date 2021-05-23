/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 11:13:01 by iidzim            #+#    #+#             */
/*   Updated: 2021/05/23 11:06:42 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../libft/libft.h"

#define PIPE 124
#define GREAT 62
#define GREATER 63 //">>"
#define LESS 60
#define DQUOTE 34
#define SQUOTE 39
#define SEMICOLON 59
#define SPACE 32
#define DOLLAR 36
#define BSLASH 92
#define TILDE 126


typedef enum t_token_type
{
	pip,
	semi,
	great,
	greater,
	less,
	id,
	illegal,
	eof
}			e_token_type;

typedef struct s_lexer
{   
	char *buffer;       // the input text
	int bufsize;        // size of the input text
	int curpos;         // absolute char position in source
	int readpos;        // after current pos
	char c;             // current char under examination
}               t_lexer;

typedef struct s_token
{
	char *value;
	e_token_type type;
}               t_token;


//get_next_token.c
t_token	*get_next_token(t_lexer *l);
t_token	*string_token(t_lexer *l);
char	*tokenize_squoted_text(t_lexer *l);
char	*tokenize_dquoted_text(t_lexer *l);
char	*tokenize_text(t_lexer *l, char *s);

//lexer.c
t_token	*init_token(e_token_type type, char *s);
t_lexer *init_lexer(char *line);
t_lexer *read_cmd();
int     valid_envar(char c);
char    *envar_token(t_lexer *l);

//lexer_utlis.c
void	readchar(t_lexer *l);
int     peek_char(t_lexer *l);
void	skip_space(t_lexer *l);
t_token	*ret_char(t_lexer *l, char c, e_token_type type);
t_token	*ret_str(t_lexer *l, char *s, int type);

//utils.c
int	ftstrcmp(char *s1, char *s2);
char *ft_strjoinchar(char *s, char c);
int	no_quotes(t_lexer *l, char c);

#endif
