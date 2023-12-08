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
#include <stddef.h>
#include <stdbool.h>

#define MAX_PATH_LENGTH 256
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
	END,      // end of cmd          
} t_token;

typedef enum e_quote 
{
    NORMAL,        // no quote
    SINGLE_QUOTE,
    DOUBLE_QUOTE,
    ESCAPED        // backslash
} t_quote;

typedef enum Bool
{
	FALSE,
	TRUE
} t_Bool;


// Structure générique pour une liste

typedef struct s_command
{
    void *data;
    char *name;
    char **args;
    int argCount;
    char    *redirectFile;
    struct s_command *next;
    struct s_command *prev;
    int		fdread;
	int		fdwrite;
    t_token tokenType;
    t_quote state;
} t_command;

typedef struct s_commandList
{
    int length;
    struct s_command *head;
    struct s_command *tail;
}   t_commandList;

typedef struct s_error
{
    t_Bool error;
    char *error_name;
    struct s_error *next;
    struct s_error *prev;
} t_error;

typedef struct s_env
{
    char *var;
    char *value;
    int *data;
    struct s_env *next;
} t_env;

typedef struct t_envList
{
    int length;
    struct s_env *head;
    struct s_env *tail;
}
    t_envList;

typedef struct s_redir
{
    char *file_name;
    int redirection_type;
    struct s_redir *next;
    struct s_redir *prev;
} t_redir;

//typedef t_list t_redirList;

typedef struct s_execute
{
    int *fd;
    int pfd[2];
    int *pid;
    int *status;
    int active;
    struct s_execute *next;
} t_execute;

//typedef t_list t_pipesList;

typedef struct s_global
{
    t_commandList *arguments;
    t_commandList *commands;
    t_command *cmd;
    t_env *envlist;
    t_redir *redirections;
    t_error *error;
    t_execute *execute;
} t_global;

typedef struct s_mini
{
    char *av;
    int numberOfCommands;
    int fd_history;
    int status;
    int stdin_fd;
    int stdout_fd;
    t_commandList *commands;
    t_global *child; // TO DO : comment rappeler t_global etant plus bas ?
    t_global *exec;  // est-ce quil faut plutot rappeler la structure NON t_global ?
    t_error *error;
} t_mini;


// Global
extern int	g_exit_code;
void		rl_replace_line(const char *str, int i);

// Main
int     main(int ac, char **av, char **envp);
void    write_inputrc(void);

// Minishell

void	exit_shell(t_mini *shell);
t_env   *ft_initialize_environment(char **env);
void	ft_initialize_minishell(t_mini *shell, t_env **env);
void	ft_exit_shell(t_mini *shell);
void	ft_custom_prompt_msg(t_mini *shell);
void    ft_manage_history(t_mini *shell, const char *input);

// Linked Lists

	// File 1
void    ft_appendToList(t_commandList *list, t_command *newCommand);
void    *ft_getLastElement(t_commandList  *head);
int		ft_isListEmpty(t_commandList  *head);
void	ft_print_list (t_commandList *head, void (*printFunction)(void *data));
void	ft_printGeneric(void *data);
    // File 2
void	    ft_iterateList(t_commandList  *head, void (*callback)(void *data));
void	    ft_freeList(t_commandList  *head);
void	    ft_freeNode(t_command  *node);
int		    ft_compareString(void *data, void *target);
t_command 	*ft_findNode(t_commandList  *head, void *target);
    // File 3
t_command 	*ft_getPreviousNode(t_commandList  *head, t_command *node);
int		    ft_getListSize(t_commandList  *head);
void        ft_removeNode(t_commandList **head, t_command *node);
t_command 	*ft_createNodeCommand(void);

// Parsing
t_env       *ft_find_envVar(t_envList *envList, const char *targetName);
int         ft_split_arg(t_commandList *commandList, char *input);
int         ft_test_parsing(t_commandList *commandList, char *input,t_env **envList);
int		    ft_str_error(char *str, int number);
void	    ft_countdown(void);
char        *ft_strtrim_with_quotes(char *str);
char        *ft_strcpy(char *dest, const char *src);
char        *ft_strndup(const char *s, size_t n);
int	        ft_is_white_space(char c);
int         ft_is_pipe_or_redir(char c);
int			ft_is_quote(char c);
void		ft_tokenize_with_quotes(char *input);
int			ft_check_quotes_error(void);
void        ft_follow_quotes_state(t_command *cmd);
void        ft_redirect_stdout(t_command *command, char *input);
void        ft_redirect_stdin(t_command *command, char *input);
void        ft_parse_pipes(t_command *commands, char *input);
int         ft_is_valid_env_char(char c);
int         ft_calculate_new_length(const char *cmd, int last_exit_status);
char        *ft_getenv_var_value(const char *name);
char        *ft_expand_env_variables(t_command *command, int last_exit_status);
t_Bool      ft_check_only_spaces(const char *str);
void        ft_init_commandList(t_commandList *commandList);
char        *extract_quoted_argument(char *input);




// Execution
void    ft_execute_command(t_command *cmd);
int     ft_is_builtins(t_command *cmd);
int		is_valid_identifier(const char *name);
void    ft_exec_external_code(t_command *cmd, t_env *envList);
void	ft_exec_cmd(t_command *cmd, t_env *envList);
void    ft_execute_external_command(char *cmdPath, char *args[], t_env *envList);
void    destroy_commands(t_commandList *commandList);
void    ft_destroy_current_shell(t_mini *shell);
void    destroy_children(t_mini *mini);
int     ft_exec_builtins(t_command *cmd,t_env **envList);
char    *find_executable_path(const char *command, t_env *envList);
void    free_split(char **array);
t_env   *ft_copy_env_list(t_env *src);
t_env   *create_node2(char *var, char *value);
char    *ft_strjoin_free(char const *s1, char const *s2, int free_s1);
void    free_split(char **arr);




// Built-ins
int		change_directory(const char *path);
int		cd(char **arguments);
int     ft_echo(t_command **args);
int 	pwd(void);
int 	ft_env(t_env **env_list);
int	    ft_unset(t_env **env_list, t_command *cmd);
char	**ft_env_duplicate(char **envp);
int     ft_error_export(char *command, char *arg, char *message, int status);
int		ft_check_wrong_char(char *str);
int 	ft_only_digit(char *str);
int	    ft_is_sep(char c);
void 	ft_exit(t_command *command);
int		check_args(char *name);
int     export_func(t_env **envlist, t_command *cmd);

// Signals
void	init_terminal_settings(void);
void	init_signals(void(*signals_handle)(int));
void	receive_signal_from_user(int signal_num);
void	handle_signal_execution(int signal_num);
int		ft_is_sep(char c);
void	free_node(t_env *new_node, t_env *tmp, char *str);

//env_list
t_env	*create_node(char *var_array);
int	    add_var_to_list(t_env **envlist, char *args);
int	    is_in_lst(char	*var, t_env **envlist);
void	add_to_list(t_env **envlist, t_env *new_node);
void	replace_in_lst(t_env *new_node, t_env **envlist);
t_env	*get_in_lst(char *var, t_env **envlist);
void	print_export_list(t_env **envlist);
t_env	*sort_list_export(t_env **envlist);
int	    count_list(t_env **list);
void	swap_nodes(t_env *tmp);
t_env	*ft_envlist_duplicate(t_env **envlist);
t_env	*dup_node(char *name, char *value);
void	delete_list(t_env *envlist);


// libft

// error / free
void	free_array(char **array);
void ft_appendToListArg(t_command *command, const char *arg);
char *ft_custom_strdup(const char *str);


#endif