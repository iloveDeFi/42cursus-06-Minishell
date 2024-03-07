/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelda <jbelda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:52:37 by jbelda            #+#    #+#             */
/*   Updated: 2024/03/07 18:52:37 by jbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../srcs/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
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
# include <sys/param.h>

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
	PIPE,
	HEREDOC,
	LPR,
	RPR,
	AND,
	OR,
	APPEND,
	OUT,
	IN,
	NOT,
	END,
	COMMAND_TYPE,
	ARGUMENT_TYPE,
	OPTION_TYPE,
	UNKNOWN_TYPE
}	t_token_type;

typedef enum e_quote
{
	NORMAL,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	ESCAPED
}	t_quote_type;

typedef enum e_redirection_type
{
	NO_REDIRECTION = 0,
	OUTPUT_REDIRECTION,
	APPEND_REDIRECTION,
	INPUT_REDIRECTION,
	HERE_DOC_REDIRECTION
}	t_redirection_type;

typedef struct s_redirection_info
{
	char				*filename;
	char				*delimiter;
	t_redirection_type	type;
}	t_redirection_info;

typedef struct s_command
{
	char				*name;
	char				**args;
	int					argcount;
	char				**envp;
	struct s_command	*next;
	struct s_env		*envlist;
	int					fdread;
	int					fdwrite;
	int					i;
	char				*end_of_file;
	t_redirection_info	redirection_info;
}	t_command;

// typedef struct s_token {
// 	char				*word;
// 	int					type;
// 	int					red;
// 	int					quote;
// 	struct s_token	*next;
// 	struct s_token	*previous;
// } t_token;

typedef struct t_token
{
	char	*word;
	char	is_in_quote;
}	t_token;

typedef struct s_error
{
	char			*error_name;
	struct s_error	*next;
	struct s_error	*prev;
}	t_error;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_mini
{
	char				*av;
	int					fd_history;
	int					stdin_fd;
	int					stdout_fd;
	struct s_command	*cmd;
	t_error				*error;
}	t_mini;

// BUILT-IN

// cd
int				cd(t_command *command);
// echo
int				echo(t_command *cmd);
// env
int				env(t_env *env_list);
void			ft_display_envlist(t_env *envList);
// exit
void			ft_exit(t_command *command);
// export_util
void			ft_split_string_export_argument(const char *arg, \
	char **name, char **value);
// export
int				ft_is_alpha(char c);
int				ft_check_variable_definition(char *arg);
int				ft_check_export_args(t_command *command);
int				ft_export(t_env **envlist, t_command *cmd);

void			ft_error_free_toks(t_token **tokens);
// pwd
int				pwd(void);
// unset
int				ft_unset(t_env **envList, t_command *cmd);
// EXECUTION
void			ft_execute(t_command *cmd, t_env *envList, char **envp);
void			ft_execute_cmds(t_command *cmd, char **envp, t_env *envList);
void			ft_execute_cmd(t_command *cmd, char **envp, t_env *envList);
// builtin
int				ft_is_builtin(t_command *cmd);
int				ft_execute_builtin(t_command *cmd, t_env *envList);
// error
bool			ft_is_only_spaces(const char *str);
void			ft_handle_only_spaces(t_mini *shell);
void			ft_check_null_av_shell(t_mini *shell);
void			ft_check_empty_av_shell(t_mini *shell);
// free
void			ft_destroy_current_shell(t_mini *mini);
void			ft_free_redirection_info(t_redirection_info *redirection_info);
void			ft_exit_shell(t_mini *shell);
void			ft_free_split(char **arr);
// heredoc
void			ft_process_here_doc_redirection(t_command *command);
int				ft_eof_is_in_string(char *here, char *eof);
int				ft_find_word(char *here, char *eof, int index);
// multi
void			ft_handle_exit_status(int exit_status);
void			ft_launch_command(t_command *command);
void			ft_setup_fd(struct s_command *command, \
	int *fd_pipe_read_tmp, int *fd_pipe);
void			ft_close_fd(struct s_command *command, \
	int *fd_pipe_read_tmp, int *fd_pipe);
void			ft_execute_multi_commands(t_command *cmd);
// path
char			**ft_split_path(char **env);
// process
void			ft_process_cd_argument(t_command *currentCommand, char *token);
// redirection
bool			ft_parse_all_redirection(char *redir, char *filename, \
	int *fdread, int *fdwrite);
bool			ft_is_redirection(char *token);
// shell
void			ft_custom_prompt_msg(t_mini *shell);
void			ft_initialize_environment(t_env **envList, char **env);
void			ft_initialize_minishell(t_mini *shell);
void			ft_execute_minishell(t_mini *shell, t_env *envList, \
	char **envp);
// signal
void			ft_init_termios(void);
void			ft_signals_handle_input(int sig);
void			ft_signals_handle_execution(int sig);
void			ft_signals_init(void (*signals_handle)(int));
// single
void			ft_execute_single_command(t_command *cmd, \
	char **envp, t_env *envList);
void			ft_execute_external_command(t_command *cmd, char **env);
void			ft_exec_external_code(t_command *command);
//void	        ft_execute_external_in_fork(t_command *cmd, char **envp);
// LINKED LIST

// add
void			ft_add_to_list(t_env **envlist, t_env *new_node);
// clean
void			ft_free_array(char **array);
void			ft_free_envlist(t_env *envList);
// create
t_env			*ft_create_node_for_envlist(char *var_array);
t_env			*ft_create_node_for_export_argument(char *name, char *value);

char			**ft_env_duplicate(char **envp);
// init

// node
// sort
t_env			*ft_insert_sorted(t_env *head, t_env *new_node);
t_env			*ft_sort_list(t_env *head);
void			ft_print_exported_vars(t_env *env_list);
// PARSING
t_command		*ft_parser(char *input, t_env *envList);
bool			ft_parse_tokens(t_command **commands, t_token **tokens);
void			ft_free_tokens(t_token **tokens);
// token
t_token			**ft_tokenize(char *input);
// type
char			*ft_strcpy(char *dest, const char *src);
void			ft_putstr_fd(char *s, int fd);
// MAIN
void			ft_exit_shell(t_mini *shell);
void			ft_found_and_replace_usd(t_token **tokens, t_env *envList);
char			*ft_replace_usd_to_env(t_env *envList, char *usd);
void			replace_env_variables_in_command(t_command *command, \
	t_env *envList);
bool			ft_check_quotes(char *input);
void			exec_cmd(t_command *command, t_env *envList);
void			ft_exec_external_code(t_command *command);
int				ft_tokenize_redirection(char *tokens);
int				ft_tokenize_redirection(char *tokens);
char			*get_filename(t_command *command, char *input);

// GLOBAL
extern int		g_exit_code;

//EXTERN
void			rl_replace_line(const char *text, int clear_undo);
char			*ft_remove_leading_spaces(char *input);
void			ft_exec_heredoc(char *end_of_file, int *fdread);
bool			ft_isspace(int c);
void			ft_set_array_to_zero(int *array, int size);
void			ft_free_tokens(t_token **tokens);
void			ft_command_add_back(t_command **commands, \
	t_command *new_command);
t_token			**ft_tokenize(char *input);
//static void     set_is_in_quote(char c, char *in_quote);
void			ft_set_array_to_zero(int *array, int size);

#endif
