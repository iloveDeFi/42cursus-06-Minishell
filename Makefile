# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bat <bat@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/07 17:02:03 by bat               #+#    #+#              #
#    Updated: 2023/10/21 15:38:53 by bat              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# FINAL EXECUTABLE NAME
NAME = minishell

# DIRECTORIES
MINISHELL_FOLDER = minishell
PARSING_FOLDER = parsing
BUILT_FOLDER = builtins
EXECUTING_FOLDER = execution
SIGNALS_FOLDER = signals
LINKED_LISTS_FOLDER = linked_lists
LIBFT_FOLDER = libft

# FILES
MAIN_FILE = main.c

MINISHELL_FILES = 		minishell.c \

PARSING_FILES = 		parser.c \

EXECUTING_FILES = 		bin.c \
						builtins.c \
						executor.c \

BULITINS_FILES = 		cd.c \
						echo.c \
						exit.c \
						export.c \
						pwd.c \
						unset.c \

SIGNALS_FILES = 		signals.c \

LINKED_LISTS_FILES = 	1_linkedList.c \
						2_linkedList.c \
						3_linkedList.c \

# GLOBAL VARIABLES
CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3 -g -Iincludes
MAKE = make -C
OBJS = $(SRCS:%.c=%.o)
RM = rm -f

all: $(NAME)

%.o: %.c
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

.PHONY:	all  clean fclean re

