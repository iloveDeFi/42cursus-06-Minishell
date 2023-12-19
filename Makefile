# FINAL EXECUTABLE NAME
NAME = minishell

# DIRECTORIES
HEADER_DIRECTORY := ./includes
SRCS_DIRECTORY := ./srcs
LIBFT_FOLDER := $(SRCS_DIRECTORY)/libft

# ALL FILES.C
MAIN_FILE := main.c

MINISHELL_FILES := $(wildcard $(SRCS_DIRECTORY)/minishell/*.c)
PARSING_FILES := $(wildcard $(SRCS_DIRECTORY)/parsing/*.c)
EXECUTING_FILES := $(wildcard $(SRCS_DIRECTORY)/execution/*.c)
BUILTIN_FILES := $(wildcard $(SRCS_DIRECTORY)/builtin/*.c)
LINKED_LIST_FILES := $(wildcard $(SRCS_DIRECTORY)/linked_list/*.c)

INCLUDES_FILES := $(wildcard $(HEADER_DIRECTORY)/*.h)

# GLOBAL VARIABLES
CC := gcc -g3 -fsanitize=address
CFLAGS := -Wall -Wextra -Werror -O3 -g -I$(HEADER_DIRECTORY)
LDFLAGS := -L/usr/local/opt/readline/lib
CPPFLAGS := -I/usr/local/opt/readline/include
#LDFLAGS := -L/opt/homebrew/opt/readline/lib
#CPPFLAGS := -I/opt/homebrew/opt/readline/include
SRCS := $(MAIN_FILE) $(MINISHELL_FILES) $(PARSING_FILES) $(EXECUTING_FILES) $(BUILTIN_FILES) $(LINKED_LIST_FILES)
OBJS := $(SRCS:.c=.o)
RM := rm -f

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) $(OBJS) -L./srcs/libft -lft $(LDFLAGS) -lreadline -o $(NAME)

libft/libft.a:
	@make -C $(LIBFT_FOLDER)

clean:
	$(RM) $(OBJS)
	@make -C $(LIBFT_FOLDER) clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT_ARCHIVES)
	@make -C $(LIBFT_FOLDER) fclean

re: fclean all

.PHONY: all clean fclean re