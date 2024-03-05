#ifndef MINISHELL_H
# define MINISHELL_H

# include "../srcs/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>
# include <termios.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdbool.h>
# include <ctype.h>
# include <sys/wait.h>

# define MAX_ARGUMENTS 100
# define MAX_PATH_LENGTH 4096
# define MAX_INPUT_SIZE 1024
# define MAX_COMMANDS 10
# define ERROR_TOO_MANY_PIPES 421
# define ERROR_IN_PIPE_EXEC 422
# define ERROR_IN_COMMAND_EXEC 423
# define ERROR_IN_REDIRECTION_EXEC 424
# define ERROR_IN_ERROR_BEFORE_EXEC 425
# define ERROR_NO_HERE_DOC_FILENAME 426
// File Descriptor
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define CD "cd"
// # define ECHO "echo"
# define ENV "env"
# define EXIT "exit"
# define EXPORT "export"
# define PWD "pwd"
# define UNSET "unset"

typedef enum e_token_type
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
    COMMAND_TYPE,
    ARGUMENT_TYPE,
    OPTION_TYPE,
    UNKNOWN_TYPE
} t_token_type;

typedef t_token_type (*TokenChecker)(char *);

typedef enum e_quote
{
    NORMAL,
    SINGLE_QUOTE,
    DOUBLE_QUOTE,
    ESCAPED
} t_quote_type;

typedef enum e_redirection_type {
    NO_REDIRECTION = 0,
    OUTPUT_REDIRECTION,     // '>' or 1
    APPEND_REDIRECTION,     // '>>' or 2
    INPUT_REDIRECTION,      // '<' or 3
    HERE_DOC_REDIRECTION    // '<<' or 4
} t_redirection_type;

typedef struct s_redirection_info
{
    char *filename;
    char *delimiter;
    t_redirection_type type;
} t_redirection_info;

typedef struct s_command
{
    char *name;
    char **args;
	int argCount;
	char **envp;
    struct s_command *next;
    struct s_env *envList;
	int fdread;
	int fdwrite;
	char *end_of_file;
	t_redirection_info redirection_info;
} t_command;

// typedef struct s_token {
// 	char				*word;
// 	int					type;
// 	int					red;
// 	int					quote;
// 	struct s_token	*next;
// 	struct s_token	*previous;
// } t_token;

typedef struct s_error
{
    char *error_name;
    struct s_error *next;
    struct s_error *prev;
} t_error;

typedef struct s_env
{
    char *name;
    char *value;
    struct s_env *next;
    struct s_env *prev;
} t_env;

typedef struct s_mini
{
    char *av;
    // int status;
    int fd_history;
    int stdin_fd;
    int stdout_fd;
	// struct s_token		*token;
	struct s_command	*cmd;
    t_error *error;
} t_mini;

// BUILT-IN

// cd
int				cd(t_command *command);
void			ft_process_cd_argument(t_command *command, char *arg);
// echo
void            ft_handle_argument(char *arg);
void            ft_handle_space();
void            ft_echo_args(char **args, int g_exit_code);
void            print_error_message(char *message);
//int             echo(char **args, int g_exit_code);
int				echo(t_command *cmd);
// env
int				env(t_env *env_list);
void			ft_display_envlist(t_env *envList);
// exit
int				ft_search_exit_arg_in_envList(t_command *command, t_env *envList);
int				ft_check_exit_arg_value(char *value);
int				ft_exit(t_command *command, t_env *envList);
// export_util
void			ft_split_string_export_argument(const char *arg, char **name, char **value);
// export
int				ft_is_alpha(char c);
int				ft_check_variable_definition(char *arg);
int				ft_check_export_args(t_command *command);
void			ft_print_exported_vars(t_env *envList);
int				ft_export(t_env **envlist, t_command *cmd);
// pwd
int				pwd(void);
// unset
int				ft_unset(t_env **envList, t_command *cmd);

// EXECUTION

// argument
char 			**ft_allocate_and_copy_arguments(t_command *command, char **oldArgs, int argCount, char *newArg);
void		 	ft_copy_existing_arguments(char **newArgs, char **oldArgs, int argCount);
void 			ft_copy_new_argument(t_command *command, char **newArgs, int argCount, char *newArg);
void 			ft_add_null_terminator(char **newArgs, int argCount);
char 			**ft_allocate_and_copy_arguments(t_command *command, char **oldArgs, int argCount, char *newArg);
// builtin
int				ft_is_builtin(t_command *cmd);
int				ft_execute_builtin(t_command *cmd, t_env *envList);
// error
bool		    ft_is_only_spaces(const char *str);
void 			ft_handle_only_spaces(t_mini *shell);
void 			ft_check_null_av_shell(t_mini *shell);
void 			ft_check_empty_av_shell(t_mini *shell);
// free
void	        ft_destroy_current_shell(t_mini *mini);
void			ft_free_redirection_info(t_redirection_info *redirection_info);
void	        ft_exit_shell(t_mini *shell);
void	        ft_free_split(char **arr);
// heredoc
void 			ft_process_here_doc_redirection(t_command *command);
int				ft_eof_is_in_string(char *here, char *eof);
int				ft_isword(char *here, char *eof, int index);
// multi
void			ft_handle_exit_status(int exit_status);
void			ft_launch_command(t_command *command);
void			ft_setup_fd(struct s_command *command, int *fd_pipe_read_tmp, int *fd_pipe);
void			ft_close_fd(struct s_command *command, int *fd_pipe_read_tmp, int *fd_pipe);
void			ft_execute_multi_commands(t_command *cmd);
// path
char            *ft_build_full_path(t_command *command);
void            ft_execute_command_with_absolute_path(t_command *command);
void            ft_execute_command_with_relative_path(t_command *command);
void            ft_execute_command_with_path(t_command *command);
char            *ft_lookfor_command_and_build_path(char *path, t_command *command);
char			**ft_split_path(char **env);
// process
void	        ft_process_command(t_command *command, char **envp, t_env *envList);
t_command       *ft_process_token_as_command(t_command *currentCommand, char *token); 
void            ft_process_token_as_argument(t_command *command, char *token);
// redirection
void 			ft_process_input_redirection(t_command *command);
void 			ft_process_output_redirection(t_command *command);
void 			ft_process_append_redirection(t_command *command);
void 			ft_process_here_doc_redirection(t_command *command);
void 			ft_launch_redirection_execution(t_command *command);
// shell
void            ft_custom_prompt_msg(t_mini *shell);
void            ft_initialize_environment(t_env **envList, char **env);
void            ft_initialize_minishell(t_mini *shell);
void            ft_execute_minishell(t_mini *shell, t_env *envList, char **envp);
// signal
// single
void	        ft_execute_single_command(t_command *cmd, char **envp, t_env *envList);
void	        ft_execute_external_command(t_command *cmd, char **env);
void	        ft_exec_external_code(t_command *command);
void	        ft_execute_external_in_fork(t_command *cmd, char **envp);
// LINKED LIST
// add
void			ft_add_to_list(t_env **envlist, t_env *new_node);
int				ft_add_envVar_to_list(t_env **envlist, t_env *new_node, t_command *command);
// void			ft_append_to_commandList(t_commandList *commandList, t_command *newNode);
// clean
void			ft_free_array(char **array);
void			ft_free_envlist(t_env *envList);
// create
t_env			*ft_create_node_for_envlist(char *var_array);
// t_command		*ft_create_new_command_in_commandList(t_commandList *commandList, char *name);
// t_command		*ft_create_init_new_command_commandList(t_commandList *commandList, char *name);
t_env			*ft_create_node_for_export_argument(char *name, char *value);
// duplicate
char			**ft_env_duplicate(char **envp);
// init
// void			ft_init_new_node_name(t_commandList *commandList, t_command *command, char *token);
// void			ft_init_new_node_args(t_commandList *commandList, t_command *command, char *token);
void			ft_init_new_node_redirection_info(t_command *command);
// void			ft_init_new_node(t_commandList *commandList, t_command *command, char *token);
// void			ft_init_new_node(t_commandList *commandList, t_command *command, char *token);
// node
t_env			*ft_find_envVar(t_env *envList, const char *targetName);

// PARSING

// custom_strtok TO DO CLEAN THIS
void            ft_print_word(const char *start, const char *end);
const char      *ft_find_next_delimiter(const char *start, char delimiter);
const char      *ft_find_closing_quote(const char *start);
void            ft_process_word(const char *start, const char *end);
void            ft_strtok_for_quotes(const char *input);
// error
int 			ft_check_if_file_exists(const char *filename);
int	            ft_check_if_its_any_white_space(char c);
bool         	ft_check_if_only_spaces(const char *str);
void            ft_initialization_of_errors(t_mini *shell);
void            ft_add_space_around_redirection(char *input);
// expansion
int             ft_is_valid_env_char(char c);
char            *ft_get_env_var_value(char *var_name);
int          	ft_calculate_var_length(char *var_name, int g_exit_code);
int          	ft_calculate_new_length(char *cmd, int g_exit_code);
void            ft_process_char(char *result, int *j, char *command, int *i);
char            *ft_expand_single_env_var(char *var_name);
char            *ft_expand_env_variables(char *command);
// handle
// void 			ft_handle_error(); TO DO SOON;
// int 			ft_handle_pipe(t_commandList *commandList, t_command *command);
// int 			ft_handle_redirection(t_commandList *commandList, t_command *command);
// int 			ft_handle_command(t_commandList *commandList, t_command *command, t_env *envList, char **envp);
// parser
int             ft_launch_parsing_and_execution(t_mini *shell, char *input, t_env *envList, char **envp);
// void			ft_process_the_first_token_as_a_command(t_commandList *commandList, char *token);
// void			ft_process_token_as_an_argument(t_commandList *commandList, t_command *command, char *token);
// pipe
void 			ft_initialize_pipes(t_command *currentCommand);
int 			ft_count_number_of_pipes(char *input);
void 			ft_close_pipes(t_command *command);
bool 			ft_check_if_pipe_in_char(char *token);
bool 			ft_check_if_pipe_in_string(char *token);
int 			ft_check_if_pipe_in_inputCopy(char *inputCopy);
// quote

// redirection
t_redirection_info	ft_parse_output_redirection(char *input);
t_redirection_info 	ft_parse_append_redirection(char *input);
t_redirection_info 	ft_parse_input_redirection(char *input);
t_redirection_info 	ft_parse_here_doc_redirection(char *input);
t_redirection_type 	ft_parse_all_redirection(char *token);
// token
char ** 		ft_tokenize_input_with_strtok(char *input);
// type
int 			ft_token_is_pipe(char *token, t_command *currentCommand);
int 			ft_token_is_redirection(char *token, t_command *currentCommand, int *tokenIndex);
// util TO DO CLEAN SI DEJA DANS LA LIBFT
char           	*ft_strcpy(char *dest, const char *src);
char           	*ft_strpbrk(const char *s1, const char *s2);
char           	*ft_custom_strdup(const char *str);
char           	*ft_strndup(const char *s, size_t n);
void			ft_putstr_fd(char *s, int fd);

// GLOBAL

extern int		g_exit_code;
void			srl_replace_line(const char *str, int i);

// MAIN
void	       	ft_exit_shell(t_mini *shell);
void            ft_found_and_replace_usd(t_command *command, t_env *envList);
char            *ft_replace_usd_to_env(t_env *envList, char *usd);
void            replace_env_variables_in_command(t_command *command, t_env *envList);

void	        ft_init_termios(void);
void	        ft_signals_handle_input(int sig);
void	        ft_signals_handle_execution(int sig);
void	        ft_signals_init(void (*signals_handle)(int));
void	        ft_remove_quotes(char *input);
bool	        ft_check_quotes(char *input);

extern void		rl_replace_line(const char *bob, int test);

void	        exec_cmd(t_command *command, t_env *envList);
void	        ft_exec_external_code(t_command *command);

#endif
