#include "minishell.h"

t_command *    ft_create_new_command(char **tokens, int arg_len, int fdwrite, int fdread)
{
	printf("ft_create_new_command\n");
	t_command *command;
	int token_index;
	int args_index;

    token_index = 0;
	args_index = 0;
	command = (t_command *)malloc(sizeof(t_command));
	// printf("%s\n", tokens[0]);
	if (ft_strcmp(tokens[token_index], ">") == 0 || ft_strcmp(tokens[token_index], ">>") == 0 || ft_strcmp(tokens[token_index], "<") == 0)// skip the redirection and the filename
		token_index += 2;
	command->name = ft_strdup(tokens[token_index]);
	command->args = (char **)malloc(sizeof(char *) * (arg_len + 2));
	command->argCount = 0;
	while(token_index < arg_len + 1)
	{
		if (ft_strcmp(tokens[token_index], ">") == 0 || ft_strcmp(tokens[token_index], ">>") == 0 || ft_strcmp(tokens[token_index], "<") == 0)// skip the redirection and the filename
		{
			token_index += 2;
			continue;
		}
		command->args[args_index] = ft_strdup(tokens[token_index]);
		args_index++;
		token_index++;
        //pritnf("command->argCount = %d\n", command->argCount);
	}
    command->argCount = args_index;
	command->args[args_index] = NULL;
	command->next = NULL;
	command->fdread = fdread;
	command->fdwrite = fdwrite;
	command->redirection_info.filename = NULL;
	command->redirection_info.delimiter = NULL;
	command->redirection_info.type = NO_REDIRECTION;
	printf("-- command->redirection_info.type = NO_REDIRECTION : %d\n", command->redirection_info.type);
	// printf("arg_len = %d\n", arg_len);
	// printf("name = %s\n", command->name);
	// i = 0;
	// while(command->args[i] != NULL)
	// {
	// 	printf("args = %s\n", command->args[i]);
	// 	i++;
	// }
	printf("argCount = %d\n", command->argCount);
	return command;
}

void ft_append_to_command(t_command **first_command, t_command *new_command)
{
	t_command *current_command;

	current_command = *first_command;
	if (*first_command == NULL)
	{
		*first_command = new_command;
		return;
	}
	while (current_command->next != NULL)
	{
		current_command = current_command->next;
	}
	current_command->next = new_command;
}

bool ft_parse_tokens(t_command **first_command, char **tokens)
{
	// dont touch at this function, I will refactor it later
	char *token;
	int arg_len;
	int tokenIndex;
	int fdwrite;
	int fdread;

	if (tokens == NULL) // is this check necessary?
		return false;

	tokenIndex = 0;
	fdwrite = 1;
	fdread = 1;
	while (tokens[tokenIndex] != NULL)
	{
		token = tokens[tokenIndex]; // is not used...
		printf("token = %s\n", token );
		if (tokens[tokenIndex + 1] == NULL || ft_strcmp(tokens[tokenIndex + 1], "|") == 0)
		{
			ft_append_to_command(first_command, ft_create_new_command(tokens, tokenIndex, fdwrite, fdread));
			tokens += tokenIndex + 1 + (tokens[tokenIndex + 1] != NULL); // bidouillage, pour skip le pipe
			tokenIndex = 0;
			fdwrite = 1;
			fdread= 0;
			continue;
		}
		// ! TODO if token is <<, >, ... we skip 2 tokens!! in create_new_command
		if (ft_strcmp(tokens[tokenIndex], "<<") == 0)
		{
			if (tokens[tokenIndex + 1] == NULL || ft_strcmp(tokens[tokenIndex + 1], "|") == 0) // TODO should only accept strings after << (but this should be enough)
			{
				ft_putstr_fd("minishell: parse error near <<\n", STDERR_FILENO);
				g_exit_code = 258;
				return false;
			}
		}
		else if (ft_strcmp(tokens[tokenIndex], ">") == 0)
		{
			if (tokens[tokenIndex + 1] == NULL || ft_strcmp(tokens[tokenIndex + 1], "|") == 0) // TODO should only accept strings after > (but this should be enough)
			{
				ft_putstr_fd("minishell: parse error near >\n", STDERR_FILENO);
				g_exit_code = 258;
				return false;
			}
			fdwrite = open(tokens[tokenIndex + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		}
		else if (ft_strcmp(tokens[tokenIndex], ">>") == 0)
		{
			if (tokens[tokenIndex + 1] == NULL || ft_strcmp(tokens[tokenIndex + 1], "|") == 0) // TODO should only accept strings after > (but this should be enough)
			{
				ft_putstr_fd("minishell: parse error near >\n", STDERR_FILENO);
				g_exit_code = 258;
				return false;
			}
			fdwrite = open(tokens[tokenIndex + 1], O_APPEND | O_CREAT | O_WRONLY, 0644);
		}
		else if (ft_strcmp(tokens[tokenIndex], "<") == 0)
		{
			if (tokens[tokenIndex + 1] == NULL || ft_strcmp(tokens[tokenIndex + 1], "|") == 0) // TODO should only accept strings after < (but this should be enough)
			{
				ft_putstr_fd("minishell: parse error near <\n", STDERR_FILENO);
				g_exit_code = 258;
				return false;
			}
			fdread = open(tokens[tokenIndex + 1], O_RDONLY);
		}

		// else if(ft_strcmp(tokens[tokenIndex + 1], "<") == 0)
		// {
		// 	printf("tokens = %s\n", *tokens);
		// 	printf("token = %s\n", token);
		// 	ft_append_to_command(first_command, ft_create_new_command(tokens, arg_len));
		// 	tokens += arg_len + 1;
		// 	printf("ju = %s\n", tokens[tokenIndex]);
		// 	printf("bat = %s\n", tokens[tokenIndex + 1]);
			// r_left(*first_command, token, &tokens[tokenIndex], &tokens[tokenIndex + 1]);
		// 	arg_len = 0;
		// 	tokenIndex = 0;
		// 	continue;
		// }
		tokenIndex++;
	}
	return true;
}

// void ft_process_tokens(t_command **command, char **tokens)
// {
//     char *token;
//     int arg_len;
//     int tokenIndex;

//     if (tokens == NULL)
//         return;

//     arg_len = 0;
//     tokenIndex = 0;
//     char **currentToken = tokens; // Pointeur temporaire pour itérer sur tokens
//     while (*currentToken != NULL)
//     {
//         token = *currentToken;
//         printf("token = %s\n", token );
//         if (ft_strcmp(token, "|") == 0 || *(currentToken + 1) == NULL)
//         {
//             ft_append_to_command(command, ft_create_new_command(tokens, arg_len));
//             printf("tokens = %s\n", *currentToken);
//             currentToken += arg_len + 1;
//             arg_len = 0;
//             tokenIndex = 0;
//             continue;

//         }
//         currentToken++;
//         arg_len++;
//         printf("currentToken = %s\n", *currentToken);
//     }
// }

// ---------------- For one command ----------------

void	ft_execute_cmd(t_command *cmd, char **envp, t_env *envList)
{
	int		original_stdin;
	int		original_stdout;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	if (cmd->fdread >= 3)
		dup2(cmd->fdread, STDIN_FILENO);
	if (cmd->fdwrite >= 3)
		dup2(cmd->fdwrite, STDOUT_FILENO);
	if (ft_is_builtin(cmd))
		g_exit_code = ft_execute_builtin(cmd, envList);
	else
		ft_execute_external_in_fork(cmd, envp);
	if (cmd->fdread >= 3)
		close(cmd->fdread);
	if (cmd->fdwrite >= 3)
		close(cmd->fdwrite);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
	close(original_stdin);
}

// ---------------- For multiple commands ----------------
static void	prepare_fds(t_command *cmd, int *fd_pipe_read_tmp,
				int *fd_pipe)
{
	close(fd_pipe[0]);
	if (cmd->fdread == 0)
		cmd->fdread = *fd_pipe_read_tmp;
	dup2(cmd->fdread, 0);
	if (cmd->fdwrite >= 3)
		close(fd_pipe[1]);
	else if (!cmd->next)
		cmd->fdwrite = 1;
	else
		cmd->fdwrite = fd_pipe[1];
	dup2(cmd->fdwrite, 1);
}

static void	close_fds(t_command *cmd, int *fd_pipe_read_tmp,
				int *fd_pipe)
{
	close(fd_pipe[1]);
	if (*fd_pipe_read_tmp >= 3)
		close(*fd_pipe_read_tmp);
	if (cmd->fdwrite >= 3)
		close(cmd->fdwrite);
	if (cmd->fdread >= 3)
		close(cmd->fdread);
	*fd_pipe_read_tmp = fd_pipe[0];
}

static void	ft_run_cmd(t_command *cmd, char **envp, t_env *envList)
{
	if (!ft_is_builtin(cmd))
		ft_execute_external_command(cmd, envp);
	exit(ft_execute_builtin(cmd, envList));
}

static void	handle_exit_status(int exit_status)
{
	if (WIFEXITED(exit_status))
		g_exit_code = WEXITSTATUS(exit_status);
	if (WIFSIGNALED(exit_status))
		g_exit_code = 128 + WTERMSIG(exit_status);
}

void	ft_execute_cmds(t_command *cmd, char **envp, t_env *envList)
{
	printf("ft_execute_cmds\n");
	int					fd_pipe_read_tmp;
	int					fd_pipe[2];
	int					exit_status;
	pid_t				fork_pid;

	fd_pipe_read_tmp = 0;
	while (cmd)
	{
		pipe(fd_pipe);
		fork_pid = fork();
		if (fork_pid == 0)
		{
			prepare_fds(cmd, &fd_pipe_read_tmp, fd_pipe);
			ft_run_cmd(cmd, envp, envList);
		}
		close_fds(cmd, &fd_pipe_read_tmp, fd_pipe);
		cmd = cmd->next;
	}
	while (waitpid(-1, &exit_status, 0) > 0)
		;
	handle_exit_status(exit_status);
}


// ---------------- Parse and launch command/s ----------------

// ? TODO : rename in ft_parsing and create a function ft_execution
int ft_launch_parsing_and_execution(t_mini *shell, char *input, t_env *envList, char **envp)
{
	t_command *first_command = NULL;

	char **tokens;
	int i = 0;

	   if(!ft_check_quotes(input))
    {
        printf(">\n");
        return 0;
    }
	ft_remove_quotes(input);
    //ft_remove_quotes(input);
    tokens = ft_tokenize_input_with_strtok(input); // TODO rename this function
	//ft_initialize_commandList(command);
	if (!ft_parse_tokens(&first_command, tokens))
	{
		// ? TODO something to free?
		return 1;
	}
	//ft_parse_all_redirection(*tokens);
    ft_token_is_a_quotes(input);

    // ft_found_and_replace_usd(first_command, envList); // ! it was making my minishell crash
	if (first_command->next == NULL) // There is only one command (-> need to fork)
		ft_execute_cmd(first_command, envp, envList);
	else
	{
		ft_execute_cmds(first_command, envp, envList);
	}

	return 0;
}
