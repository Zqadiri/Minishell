# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zqadiri <zqadiri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/08 15:30:22 by zqadiri           #+#    #+#              #
#    Updated: 2021/07/10 18:54:47 by zqadiri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

SRCS 			=	./sources/minishell.c\
					./sources/parsing/get_next_token.c\
					./sources/parsing/lexer.c\
					./sources/parsing/lexer_utils.c\
					./sources/parsing/parser_utils.c\
					./sources/parsing/ast.c\
					./sources/parsing/utils.c\
					./sources/parsing/parser.c\
					./sources/parsing/free.c
					
					
LIBFT_PATH 		= 	./libft

# SRCB			=	./sources/parsing/handle_quotes_bonus.c

SRCS_EXEC		=	./sources/execution/utils.c\
					./sources/execution/cd_builtin.c\
					./sources/execution/env_builtin.c\
					./sources/execution/exit_builtin.c\
					./sources/execution/main_exec.c\
					./sources/execution/pwd_builtin.c\
					./sources/execution/echo_builtin.c\
					./sources/execution/unset_builtin.c\
					./sources/execution/export/helpers.c\
					./sources/execution/export/export_builtin.c
					
LIBFT_PATH 		= 	./libft

OBJS			= 	${SRCS:.c=.o}
OBJS_EXEC		= 	${SRCS_EXEC:.c=.o}
# OBJB			=	$(SRCB:.c=.o)
# fix header

INCLUDE 		= 	-I includes -L includes
CC				= 	gcc
FLAGS           =  -Wall -Wextra -Werror -ltermcap -lreadline -g -fsanitize=address
RM				= 	rm -f
LIBFLAGS 		= 	-I ./libft -L ./libft -L . ./libft/*.c 

all:			 ${NAME} libft_all

$(NAME):		${OBJS} 
				@$(CC) -o $(NAME) $(SRCS) $(SRCS_EXEC) $(INCLUDE) $(LIBFLAGS) $(FLAGS) -g

# bonus:			${OBJS} ${OBJB}
# 				@$(CC) -o $(NAME) $(SRCS) $(SRCB) $(SRCS_EXEC) $(INCLUDE) $(LIBFLAGS) $(FLAGS) -g
				
clean:			libft_clean
				@${RM} ${OBJS} ${OBJS_EXEC}

fclean:			libft_fclean clean
				@${RM} ${NAME}

re:				fclean all

run:			re
				./minishell

# make other makefiles compile with the -C flag
# The -C flag makes you go to the appropriate path and do the asked command

libft_all:
				@make -C $(LIBFT_PATH) all
				@cp ./libft/libft.a libft.a

libft_clean:
				@make -C $(LIBFT_PATH) clean

libft_fclean:
				@make -C $(LIBFT_PATH) fclean
				@$(RM) libft.a
				
.PHONY: 		all fclean clean re
