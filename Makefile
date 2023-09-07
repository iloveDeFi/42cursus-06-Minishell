# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bat <bat@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/07 17:02:03 by bat               #+#    #+#              #
#    Updated: 2023/09/07 22:23:25 by bat              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGES = -Wall -Wextra -Werror -O3 -g -Iincludes

SRCS = parsing.c \
		minishell.c \

OBJS = $(SRCS:%.c=%.o)

RM = rm -f

all: 				$(NAME)

%.o: 				%.c
					${CC} ${CFLAGS} 

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) $^ $(NAME)
	
libft/libft.a:
					@make -C libft

clean:
	${RM} $(OBJS)
	@make -C libft clean
	

fclean: clean
	${RM} $(NAME)
	${RM} libft/libft.a
	@make -C libft fclean


re: fclean all

.PHONY:				all  clean fclean re

