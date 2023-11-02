# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julienbelda <julienbelda@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/07 17:02:03 by bat               #+#    #+#              #
#    Updated: 2023/11/02 13:16:53 by julienbelda      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# FINAL EXECUTABLE NAME
NAME = minishell

# DIRECTORIES
MINISHELL_FOLDER =		minishell
PARSING_FOLDER = 		parsing
BUILT_FOLDER = 			builtins
EXECUTING_FOLDER = 		execution
SIGNALS_FOLDER = 		signals
LINKED_LISTS_FOLDER = 	linked_lists
HEADER_DIRECTORY := 	./includes
SRCS_DIRECTORY := 		./srcs
LIBFT_FOLDER =			$(SRCS_DIRECTORY)/libft
LIBFT_HEADER = 			$(SRCS_DIRECTORY)/libft/libft.h
LIBFT_ARCHIVES = 		$(SRCS_DIRECTORY)/libft/libft.a


# ALL FILES.C
MAIN_FILE = main.C

MINISHELL_FILES = 		minishell.c

PARSING_FILES = 		parser.c \
						error.c

EXECUTING_FILES = 		bin.c \
						builtin.c \
						executor.c

BUILTINS_FILES = 		cd.c \
						echo.c \
						exit.c \
						export.c \
						pwd.c \
						unset.c

SIGNALS_FILES = 		signals.c \

LINKED_LISTS_FILES = 	1_linkedList.c \
						2_linkedList.c \
						3_linkedList.c
						
INCLUDES_FILES = 		minishell.h

# GLOBAL VARIABLES
MAKE = make -C
CC = gcc -g3 -fsanitize=address
CFLAGS = -Wall -Wextra -Werror -O3 -g -Iincludes
SRCS = $(MAIN_FILE) \
$(addprefix $(SRCS_DIRECTORY)/builtins/, $(BUILTINS_FILES)) \
$(addprefix $(SRCS_DIRECTORY)/minishell/, $(MINISHELL_FILES)) \
$(addprefix $(SRCS_DIRECTORY)/parsing/, $(PARSING_FILES)) \
$(addprefix $(SRCS_DIRECTORY)/execution/, $(EXECUTING_FILES)) \
$(addprefix $(SRCS_DIRECTORY)/linked_lists/, $(LINKED_LISTS_FILES)) \
$(addprefix $(SRCS_DIRECTORY)/signals/, $(SIGNALS_FILES))
OBJS = $(SRCS:.c=.o)
RM = rm -f

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
all: $(NAME)

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L./srcs/libft -lft -lreadline 
	
libft/libft.a:
	@make -C $(LIBFT_FOLDER)

$(SRCS_DIRECTORY)/%.o: $(SRCS_DIRECTORY)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	@make -C $(LIBFT_FOLDER) clean
	
fclean: clean
	${RM} $(NAME)
	${RM} $(LIBFT_ARCHIVES)
	@make -C $(LIBFT_FOLDER) fclean

re: fclean all

.PHONY:	all  clean fclean re
