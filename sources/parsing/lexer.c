/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 13:44:58 by iidzim            #+#    #+#             */
/*   Updated: 2021/04/23 10:47:21 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void readchar(t_lexer *t)
{
    if (!t || !t->buffer)
        printf("error\n");
    if (t->readpos >= t->bufsize)
        t->c = 0; //EOF
    else
        t->c = t->buffer[t->readpos];
    t->curpos = t->readpos;
    t->readpos++;
}

int peek_char(t_lexer *t)
{
    if (t->readpos >= t->bufsize)
        return (0);
    else
        return (t->buffer[t->readpos]);
}

void skip_space(t_lexer *t)
{
    if (!t || !t->buffer)
        printf("error\n");
    while(t->c == SPACE || t->c == '\t' || t->c == '\r' || t->c == '\n')
        readchar(t);
}

//page 17
t_lexer next_token(t_lexer *t)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    skip_space(t);
    if (t->c == '|')
    {
        if (peek_char(t) == SPACE && isalnum(peek_char(t)))
            token->type = PIPE;
        else
            token->type = ILLEGAL;
        token->value = t->c;
    }
    else if (t->c == ';')
    {
        if (peek_char(t->c) == SEMICOLON || peek_char(t->c) == PIPE)
        token->value = t->c;
        token->type = SEMICOLON;
    }
    else if (t->c == '>')
    {
        token = create_token(token, GREAT, t->c);
        // token->value = t->c;
        // token->type = GREAT;
    }
    else if (t->c == '>>')
    {
        token = create_token(token, GREATER, t->c);
        // token->value = t->c;
        // token->type = GREATER;
    }
    else if (t->c == '<')
    {
        token = create_token(token, LESS, t->c);
        token->value = t->c;
        token->type = LESS;
    }
    else if (isalnum(t->c) || ft_strchar("._-/$\\", t->c))
    {
        token = create_token(token, LITERAL, t->c);
        token->value = t->c;
        token->type = LITERAL;
    }
    else
    {
        // !valid_char()
    }
}

t_token *create_token(t_token *token, char *type, char c)
{
    token->value = c;
    token->type = type;
    return (token);
}

int valid_cmd(char *s)
{
    if (ft_strcmp(s, "echo"))
    {   
    }
    else if (ft_strcmp(s, "cd"))
    { 
    }
    else if (ft_strcmp(s, "pwd"))
    {
    }
    else if (ft_strcmp(s, "export"))
    {
    }
    else if (ft_strcmp(s, "unset"))
    {
    }
    else if (ft_strcmp(s, "env"))
    {
    }
    else
        return (0);
    return (1);
}