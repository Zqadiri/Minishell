# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/08 15:30:22 by zqadiri           #+#    #+#              #
#    Updated: 2021/04/08 17:24:50 by iidzim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

SRCS 			=	./sources/minishit.c\
					./sources/main_exec.c\
					
LIBFT_PATH 		= 	./libft



OBJS			= 	${SRCS:.c=.o}
INCLUDE 		= 	./includes/minishell.h
CC				= 	gcc  -Wall -Wextra -Werror
RM				= 	rm -f
LIBFLAGS 		= 	-I ./libft -L ./libft -L . ./libft/*.c 

all:			 ${NAME} libft_all

$(NAME):		${OBJS} 
				$(CC) -o $(NAME)  $(SRCS) $(LIBFLAGS)

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