# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/08 15:30:22 by zqadiri           #+#    #+#              #
#    Updated: 2021/05/17 11:37:17 by zqadiri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

SRCS 			=	./sources/minishell.c\
					./sources/execution/main_exec.c\
					./sources/parsing/lexer.c\
					./sources/parsing/parser.c\
					./sources/parsing/ast.c\

					# ./sources/parsing/list.c

SRCS_EXEC		=	./sources/execution/utils.c\
					./sources/execution/env_builtin.c\
					./sources/execution/unset_builtin.c\
					./sources/execution/cd_builtin.c

LIBFT_PATH 		= 	./libft

OBJS			= 	${SRCS:.c=.o}
OBJS_EXEC		= 	${SRCS_EXEC:.c=.o}

INCLUDE 		= 	./includes/minishell.h
CC				= 	gcc -Wall -Wextra -Werror 
RM				= 	rm -f
LIBFLAGS 		= 	-I ./libft -L ./libft -L . ./libft/*.c 

all:			 ${NAME} libft_all

$(NAME):		${OBJS} 
				$(CC) -o $(NAME) $(SRCS) $(SRCS_EXEC) $(LIBFLAGS) -g -fsanitize=address

clean:			libft_clean
				${RM} ${OBJS} ${OBJS_EXEC}
fclean:			libft_fclean clean
				${RM} ${NAME}
re:				fclean all

# make other makefiles compile with the -C flag
# The -C flag makes you go to the appropriate path and do the asked command

libft_all:
				make -C $(LIBFT_PATH) all
				cp ./libft/libft.a libft.a

libft_clean:
				make -C $(LIBFT_PATH) clean

libft_fclean:
				make -C $(LIBFT_PATH) fclean
				$(RM) libft.a
				
.PHONY: 		all fclean clean re