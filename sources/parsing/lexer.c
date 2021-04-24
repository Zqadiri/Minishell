/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 13:44:58 by iidzim            #+#    #+#             */
/*   Updated: 2021/04/24 16:40:04 by iidzim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void readchar(t_lexer *l)
{
    if (!l || !l->buffer)
        printf("error\n");
    if (l->readpos >= l->bufsize)
        l->c = 0; //EOF
    else
        l->c = l->buffer[l->readpos];
    l->curpos = l->readpos;
    l->readpos++;
}

int peek_char(t_lexer *l)
{
    if (l->readpos >= l->bufsize)
        return (0);
    else
        return (l->buffer[l->readpos]);
}

void skip_space(t_lexer *l)
{
    if (!l || !l->buffer)
        printf("error\n");
    while(l->c == SPACE || l->c == '\t' || l->c == '\r' || l->c == '\n')
        readchar(l);
}


t_token *next_token(t_lexer *l)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    skip_space(l);
    if (l->c == '|')
    {
        if (peek_char(l) == SPACE || isalnum(peek_char(l)) || peek_char(l) == GREATER)
            token->type = "PIPE";
        else
            token->type = "ILLEGAL";
        token->value = &l->c;
    }
    else if (l->c == ';')
    {
        if (peek_char(l->c) == "SEMICOLON" || peek_char(l->c) == "PIPE")
            token = create_token(token, "ILLEGAL", l->c);
        else
            token = create_token(token, "SEMICOLON", l->c);
    }
    else if (l->c == '>')
    {
        if (peek_char(l->c) == '>')
            token = create_token(token, "GREATER", l->c);
        else
            token = create_token(token, "GREAT", l->c);
    }
    else if (l->c == '<')
    {
        token = create_token(token, "LESS", l->c);
        //syntax error
    }
    else if (l->c == '\'')
    {
        token = create_token(token, "SQUOTE", l->c);
        //syntax error
    }
    else if (l->c == '\"')
    {
        token = create_token(token, "DQUOTE", l->c);
        //syntax error
    }
    else if (l->c == '$')
    {
        token = create_token(token, "DOLLAR", l->c);
        //syntax error
    }
    else if (l->c == 0)
        token = create_token(token, "EOC", "");
    else if (isalnum(l->c) || ft_strchar("._-/$\\", l->c))
    {
        token->value = read_identifier(l);
        token->type = lookupident(token->value);
        // parse quoted text
    }
    else
        // Invalid character in input return NOTOKEN;
        token = create_token(token, "ILLEGAL", l->c);
}

char *lookupident(char *s)
{
    int i;

    i = 0;
    if (valid_cmd(s))
        s = CMD;
    else if (s[i] = '-' && ft_isalpha(s[i+1]))
        s = OPTION;
    else
        s = PARAM;
    return (s);
}

char *read_identifier(t_lexer *l)
{
    char *s;
    int pos;
    
    if (!(s = malloc(sizeof(char)*20)))
        return (NULL);
    s = ft_memset(s, 0, 20);
    pos = 0;
    // printf("current char : %c \n", l->c);
    while(isalnum(l->c) || ft_strchar("._-/$\\", l->c))
    {
        if (l->c == '\\')
            readchar(l);
        s[pos++] = l->c;
        readchar(l);
        s[pos++] = l->c;
        //check DQUOTE & SQUOTE
    }
    return (s);
}

t_token *create_token(t_token *token, char *type, char c)
{
    token->value = c;
    token->type = type;
    return (token);
}

int valid_cmd(char *s)
{
    if (!ft_strcmp(s, "echo"))
    {   
    }
    else if (!ft_strcmp(s, "cd"))
    { 
    }
    else if (!ft_strcmp(s, "pwd"))
    {
    }
    else if (!ft_strcmp(s, "export"))
    {
    }
    else if (!ft_strcmp(s, "unset"))
    {
    }
    else if (!ft_strcmp(s, "env"))
    {
    }
    else
        return (0);
    // add condition for built-in function
    return (1);
}

void lexer(t_lexer *l)
{
    t_token *tok;

    while (l->c != 0)
    {
        // tok = malloc(sizeof(t_token));
        tok = next_token(l);
        // tok->value = ft_strjoin(tok->value, l->c)
        printf("value>> %s | type>> %s\n", tok->value, tok->type);
    }
}

