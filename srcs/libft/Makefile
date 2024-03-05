# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thomas <thfavre@student.42lausanne.ch>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/27 17:04:37 by bbessard          #+#    #+#              #
#    Updated: 2024/03/05 03:39:54 by thomas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INCLUDES    = -I includes -I $(LIBFT_DIR)/includes/

LIBFT_DIR   = libft/

CC = gcc

CFLAGS =  -O3 # -Wall -Wextra -Werror # TODO remove comment

RM = rm -f

LDFLAGS = -L.

LDLIBS = -lft

HDDIRS = -I includes/

AR = ar rc

HEADER = libft.h

SRC = $(wildcard ft_strtok.c) \
$(wildcard *.c)

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean git norminette re
