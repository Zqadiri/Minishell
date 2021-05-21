#include "../includes/minishell.h"

// char *read_cmd(void)
// {
//     char buf[1024];
//     char *ptr = NULL;
//     char ptrlen = 0;
//     while(fgets(buf, 1024, stdin))
//     {
//         int buflen = strlen(buf);
//         if(!ptr)
//         {
//             ptr = malloc(buflen+1);
//         }
//         else
//         {
//             char *ptr2 = realloc(ptr, ptrlen+buflen+1);
//             if(ptr2)
//             {
//                 ptr = ptr2;
//             }
//             else
//             {
//                 free(ptr);
//                 ptr = NULL;
//             }
//         }
//         if(!ptr)
//         {
//             fprintf(stderr, "error: failed to alloc buffer: %s\n", strerror(errno));
//             return NULL;
//         }
//         strcpy(ptr+ptrlen, buf);
//         if(buf[buflen-1] == '\n')
//         {
//             if(buflen == 1 || buf[buflen-2] != '\\')
//             {
//                 return ptr;
//             }
//             ptr[ptrlen+buflen-2] = '\0';
//             buflen -= 2;
//             print_prompt2();
//         }
//         ptrlen += buflen;
//     }
//     return ptr;
// }

#define EOF             (-1)
#define ERRCHAR         ( 0)
#define INIT_SRC_POS    (-2)

struct source_s
{   
    char *buffer;       /* the input text */
    long bufsize;       /* size of the input text */
    long  curpos;       /* absolute char position in source */
};

void unget_char(t_lexer *t)
{
    if(t->curpos < 0)
        return;
    t->curpos--;
}

char next_char(t_lexer *t)
{
    char c1 = 0;

    if(!t || !t->buffer)
    {
        errno = ENODATA;
        return ERRCHAR;
    }
    if(t->curpos == INIT_SRC_POS)
        t->curpos  = -1;
    else
        c1 = t->buffer[t->curpos];
    if(++t->curpos >= t->bufsize)
    {
        t->curpos = t->bufsize;
        return EOF;
    }
    return t->buffer[t->curpos];
}

char peek_char(t_lexer *t)
{
    long pos = t->curpos;

    if(!t || !t->buffer)
    {
        errno = ENODATA;
        return ERRCHAR;
    }
    if(pos == INIT_SRC_POS)
        pos++;
    pos++;
    if(pos >= t->bufsize)
        return EOF;
    return t->buffer[pos];
}

void skip_white_spaces(t_lexer *t)
{
    char c;

    if(!t || !t->buffer)
        return;
    while(((c = peek_char(t)) != EOF) && (c == ' ' || c == '\t'))
        next_char(t);
}

char *tok_buf = NULL;
int   tok_bufsize  = 0;
int   tok_bufindex = -1;

struct token_s *tokenize(struct source_s *src)
{
    int  endloop = 0;

    if(!src || !src->buffer || !src->bufsize)
    {
        errno = ENODATA;
        return &eof_token;
    }
    
    if(!tok_buf)
    {
        tok_bufsize = 1024;
        tok_buf = malloc(tok_bufsize);
        if(!tok_buf)
        {
            errno = ENOMEM;
            return &eof_token;
        }
    }

    tok_bufindex     = 0;
    tok_buf[0]       = '\0';

    char nc = next_char(src);

    if(nc == ERRCHAR || nc == EOF)
    {
        return &eof_token;
    }

    do
    {
        switch(nc)
        {
            case ' ':
            case '\t':
                if(tok_bufindex > 0)
                {
                    endloop = 1;
                }
                break;
                
            case '\n':
                if(tok_bufindex > 0)
                {
                    unget_char(src);
                }
                else
                {
                    add_to_buf(nc);
                }
                endloop = 1;
                break;
                
            default:
                add_to_buf(nc);
                break;
        }

        if(endloop)
        {
            break;
        }

    } while((nc = next_char(src)) != EOF);

    if(tok_bufindex == 0)
    {
        return &eof_token;
    }
    
    if(tok_bufindex >= tok_bufsize)
    {
        tok_bufindex--;
    }
    tok_buf[tok_bufindex] = '\0';

    struct token_s *tok = create_token(tok_buf);
    if(!tok)
    {
        fprintf(stderr, "error: failed to alloc buffer: %s\n", strerror(errno));
        return &eof_token;
    }

    tok->src = src;
    return tok;
}


///

