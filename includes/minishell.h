#ifndef MINISHELL_H
# define MINISHELL_H

#include "../srcs/libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>

# define  MAX_INPUT_SIZE 1024

# define STDIN 0
# define STDOUT 1
# define STDERR 2
typedef enum
{
    FALSE,
    TRUE
}   Bool;

// Built-ins


// Excecution  

// libft


// Linked Lists


// Parsing
int	ft_str_error(char *str, int number);

typedef struct s_arg
{
    char *name;
    struct s_arg *next;
    struct s_arg *prev;
}   t_arg;
typedef struct s_argList
{
    int listLength;
    struct t_arg *head;
    struct t_arg *tail;
} t_argList;

typedef struct s_command
{
    char *name;
    char **arguments;
    struct s_command *head;
    struct s_command *tail;// Un tableau de chaînes pour les arguments
}   t_command;
typedef struct s_commandList
{
    int commandListLength;
    char *name;
    struct t_command *head;
    struct t_command *tail;
}   t_commandList;

typedef struct s_envVar
{
    char *name;
    char *value;
    struct s_envVar *next;
    struct s_envVar *prev;
}   t_env;  
typedef struct s_envVarList 
{
    int envVarListLength;
    struct t_envVar *head;
    struct t_envVar *tail;
}   t_envList;

typedef struct s_redir
{
    char *file_name;
    int redirection_type;
    struct s_redir *next;
    struct s_redir *prev;
}   t_redir;

int cd(t_command *command);
int echo(int ac, char **av);
void	pwd(void);
// Signals

#endif