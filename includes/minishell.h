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

// Structures
typedef struct s_node 
{
    void *data;
    struct s_node *next;
    struct s_node *prev;
} t_node;
typedef struct s_arg
{
    char *name;
    struct s_arg *next;
    struct s_arg *prev;
} t_arg;
typedef struct s_argList
{
    int arglistLength;
    struct t_arg *head;
    struct t_arg *tail;
} t_argList;

typedef struct s_command
{
    char *name;
    char **arguments;
    struct s_command *head;
    struct s_command *tail;// Un tableau de chaînes pour les arguments
} t_command;
typedef struct s_commandList
{
    int commandListLength;
    char *name;
    struct t_command *head;
    struct t_command *tail;
} t_commandList;

typedef struct s_envVar
{
    char *name;
    char *value;
    struct s_envVar *next;
    struct s_envVar *prev;
} t_envVar;  
typedef struct s_envVarList 
{
    int envVarListLength;
    struct t_envVar *head;
    struct t_envVar *tail;
} t_envVarList;

typedef struct s_redir
{
    char *file_name;
    int redirection_type;
    struct s_redir *next;
    struct s_redir *prev;
} t_redir;

typedef struct s_redirList
{
    int redirListLength;
    struct t_redir *head;
    struct t_redir *tail;
} t_redirList;

typedef struct s_pipes
{
    int pfd[2];
    int pid;
} t_pipes;

typedef struct s_global
{
    t_argList *arguments;
    t_envVarList *envVars;
    t_commandList *commands;
    t_redirList *redirections;
    t_pipes *pipes;
} t_global;

// Signals

// Linked Lists
// File 1
void appendToList(t_node **head, void *data);
void    *getLastElement(t_node *head);
int isListEmpty(t_node *head);
void	print_list(t_node *head, void (*printFunction)(void *data));
void printGeneric(void *data);
// File 2
void iterateList(t_node *head, void (*callback)(void *data));
void freeList(t_node *head);
void freeNode(t_node *node);
int compareString(void *data, void *target);
t_node *findNode(t_node *head, void *target);
// File 3
t_node *getPreviousNode(t_node *head, t_node *node);
int getListSize(t_node *head);
void removeNode(t_node **head, t_node *node);

// Built-ins

// Execution  

// libft

// Parsing
int	ft_str_error(char *str, int number);

#endif