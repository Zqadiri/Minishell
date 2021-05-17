# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/08 15:30:22 by zqadiri           #+#    #+#              #
#    Updated: 2021/05/17 09:21:31 by zqadiri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

SRCS 			=	./sources/minishell.c\
					./sources/execution/main_exec.c\
					./sources/parsing/lexer.c\
					./sources/parsing/parser.c\
					./sources/parsing/ast.c\
					./sources/execution/utils.c
					# ./sources/parsing/list.c
					

LIBFT_PATH 		= 	./libft

OBJS			= 	${SRCS:.c=.o}
INCLUDE 		= 	./includes/minishell.h
CC				= 	gcc -Wall -Wextra -Werror 
RM				= 	rm -f
LIBFLAGS 		= 	-I ./libft -L ./libft -L . ./libft/*.c 

all:			 ${NAME} libft_all

$(NAME):		${OBJS} 
				$(CC) -o $(NAME) $(SRCS) $(LIBFLAGS) -g -fsanitize=address

clean:			libft_clean
				${RM} ${OBJS}
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