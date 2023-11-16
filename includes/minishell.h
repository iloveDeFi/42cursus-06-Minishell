#ifndef MINISHELL_H
# define MINISHELL_H

#include "../srcs/libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <termios.h>
#include <fcntl.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

# define  MAX_INPUT_SIZE 1024
// File Descriptor
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define CD "cd"
//# define ECHO "echo"
# define ENV "env"
# define EXIT "exit"
# define EXPORT "export"
# define PWD "pwd"
# define UNSET "unset"

typedef enum e_token
{
	PIPE,     // |
	HEREDOC,  // <<
	LPR,      // (
	RPR,      // )
	AND,      // &&
	OR,       // ||
	APPEND,   // >>
	OUT,      // >
	IN,       // <
	NOT,      // string
	END       // end of cmd
}t_token;

typedef enum
{
	FALSE,
	TRUE
}   Bool;

/*typedef struct s_mini
{
    char *av;
    int numberOfCommands;
    int fd_history;
	int status;
	int stdin_fd;
	int stdout_fd;
    t_global *child; // pour pointer faire t_mini.child->enVars etc
    t_global *exec;
    t_global *errors;*/
/*/}   t_mini;

typedef struct s_env
{
    char *var;
    char *value;
    struct s_env *next;
} t_env;

typedef struct s_envList
{
    int envListLength;
    t_env *head;
    t_env *tail;
} t_envList;

// Structures
typedef struct s_node 
{
	void *data;
	struct s_node *next;
	struct s_node *prev;
} t_node;

typedef struct s_nodeList
{
    int nodeListLength;
    t_node *head;
    t_node *tail;
} t_nodeList;

typedef struct s_arg
{
	char *name;
	struct s_arg *next;
	struct s_arg *prev;
} t_arg;

typedef struct s_argList
{
    int arglistLength;
    t_arg *head;
    t_arg *tail;
} t_argList;

typedef struct s_command
{
    char *name;
    char **arguments;
    struct s_command *next;
    struct s_command *prev;// Un tableau de chaînes pour les arguments
} t_command;

typedef struct s_commandList
{
    int commandListLength;
    char *name;
    t_command *head;
    t_command *tail;
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
    t_envVar *head;
    t_envVar *tail;
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
    t_redir *head;
    t_redir *tail;
} t_redirList;

typedef struct s_pipes
{
	int pfd[2];
	int pid;
} t_pipes;

typedef struct s_pipesList
{
    int pipeslistLength;
    t_pipes *head;
    t_pipes *tail;
} t_pipesList;

typedef struct s_global
{
	t_argList *arguments;
	t_envVarList *envVars;
	t_commandList *commands;
	t_redirList *redirections;
	t_pipes *pipes;
} t_global;*/



// Structure générique pour un nœud
typedef struct s_node 
{
    void *data;
    struct s_node *next;
    struct s_node *prev;
} t_node;

// Structure générique pour une liste
typedef struct s_list
{
    int length;
    t_node *head;
    t_node *tail;
} t_list;

typedef struct s_arg
{
    char *name;
    struct s_arg *next;
    struct s_arg *prev;
} t_arg;

typedef t_list t_argList;

typedef struct s_command
{
    char *name;
    char **arguments;
    struct s_command *next;
    struct s_command *prev;
} t_command;

typedef t_list t_commandList;

typedef struct s_env
{
    char *var;
    char *value;
    struct s_env *next;
} t_env;

typedef t_list t_envList;

typedef struct s_envVar
{
    char *name;
    char *value;
    struct s_envVar *next;
    struct s_envVar *prev;
} t_envVar;

typedef t_list t_envVarList;

typedef struct s_redir
{
    char *file_name;
    int redirection_type;
    struct s_redir *next;
    struct s_redir *prev;
} t_redir;

typedef t_list t_redirList;

typedef struct s_pipes
{
    int pfd[2];
    int pid;
} t_pipes;

typedef t_list t_pipesList;

typedef struct s_global
{
    t_argList *arguments;
    t_envVarList *envVars;
    t_commandList *commands;
    t_redirList *redirections;
    t_pipesList *pipes;
} t_global;

typedef struct s_mini
{
    char *av;
    int numberOfCommands;
    int fd_history;
    int status;
    int stdin_fd;
    int stdout_fd;
    t_global *child; // pour pointer faire t_mini.child->enVars etc
    t_global *exec;
    t_global *errors;
} t_mini;




// Global
extern int	g_exit_code;
void		rl_replace_line(const char *str, int i);

// Main
int     main(int ac, char **av, char **envp);
void    write_inputrc(void);

// Minishell

void	ft_initialize_environment(t_envList *envList, char **env);
void	ft_initialize_minishell(t_mini *shell, t_env **env);
void	ft_exit_shell(t_mini *shell);
void    ft_custom_prompt_msg(t_mini *shell);


// Linked Lists
    // File 1
void	appendToList(t_node **head, void *data);
void    *getLastElement(t_node *head);
int		isListEmpty(t_node *head);
void	print_list(t_node *head, void (*printFunction)(void *data));
void	printGeneric(void *data);
    // File 2
void	iterateList(t_node *head, void (*callback)(void *data));
void	freeList(t_node *head);
void	freeNode(t_node *node);
int		compareString(void *data, void *target);
t_node	*findNode(t_node *head, void *target);
    // File 3
t_node	*getPreviousNode(t_node *head, t_node *node);
int		getListSize(t_node *head);
void	removeNode(t_node **head, t_node *node);
t_node	*ft_createNode(void *data);

// Parsing
t_envVar    *ft_find_envVar(t_envVar *head, const char *targetName);
int		    ft_split_arg(t_argList *argList, char *input);
int		    ft_str_error(char *str, int number);
void	    ft_countdown(void);
char        *ft_strtrim_with_quotes(char *str);
char        *ft_strcpy(char *dest, const char *src);
int	        ft_is_white_space(char c);
int         ft_is_pipe_or_redir(char c);
int         ft_is_quote(char c);
void        ft_tokenize_with_quotes(char *input);
int         ft_check_quotes_error(void);

// Execution
void    ft_execute_command(t_command *command);

// Built-ins
int		change_directory(const char *path);
int		cd(t_command *command);
int		echo(int ac, char **av);
void    pwd(void);
void    ft_env(t_envList *env_list);
char	**ft_env_duplicate(char **envp);
int		ft_error_export(char *args);
int		ft_check_wrong_char(char *str);
int 	ft_only_digit(char *str);
int	    ft_is_sep(char c);


// Signals
void	init_terminal_settings(void);
void	init_signals(void(*signals_handle)(int));
void	receive_signal_from_user(int signal_num);
void	handle_signal_execution(int signal_num);
int		ft_is_sep(char c);

// libft

// error / free
void	free_array(char **array);

#endif