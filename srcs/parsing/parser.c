#include "minishell.h"

t_command *    ft_create_new_command(char **tokens, int arg_len)
{
	printf("ft_create_new_command\n");
	t_command *command;
	int i;

    i = 0;
	command = (t_command *)malloc(sizeof(t_command));
	// printf("%s\n", tokens[0]);
	command->name = ft_strdup(tokens[0]);
	command->args = (char **)malloc(sizeof(char *) * (arg_len + 2));
	while(i < arg_len + 1)
	{
		command->args[i] = ft_strdup(tokens[i]);
		i++;
        command->argCount = i;
        //pritnf("command->argCount = %d\n", command->argCount);
	}
	command->args[i] = NULL;
	command->next = NULL;
	command->fdread = 0;
	command->fdwrite = 1;
	// printf("arg_len = %d\n", arg_len);
	// printf("name = %s\n", command->name);
	i = 0;
	// while(command->args[i] != NULL)
	// {
	// 	printf("args = %s\n", command->args[i]);
	// 	i++;
	// }
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

void ft_parse_tokens(t_command **first_command, char **tokens)
{
	// dont touch at this function, I will refactor it later
	char *token;
	int arg_len;
	int tokenIndex;

	if (tokens == NULL)
		return;

	arg_len = 0;
	tokenIndex = 0;
	while (tokens[tokenIndex] != NULL)
	{
		token = tokens[tokenIndex];
		// printf("token = %s\n", token );
		if (tokens[tokenIndex + 1] == NULL)
		{
			ft_append_to_command(first_command, ft_create_new_command(tokens, arg_len));
			tokens += arg_len + 1;
			arg_len = 0;
			tokenIndex = 0;
			continue;
		}
		if (ft_strcmp(tokens[tokenIndex + 1], "|") == 0)
		{
			ft_append_to_command(first_command, ft_create_new_command(tokens, arg_len));
			tokens += arg_len + 2;
			arg_len = 0;
			tokenIndex = 0;
			continue;
		}
		tokenIndex++;
		arg_len++;
	}
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
static void	ft_execute_external_in_fork(t_command *cmd, char **envp)
{
	pid_t	fork_pid;
	int     exit_code;

	fork_pid = fork();
	if (fork_pid == 0)
		ft_execute_external_command(cmd, envp);
	waitpid(fork_pid, &exit_code, 0);
	if (WIFEXITED(exit_code))
		g_exit_code = WEXITSTATUS(exit_code);
	if (WIFSIGNALED(exit_code))
		g_exit_code = 128 + WTERMSIG(exit_code);
}

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
int ft_launch_parsing_and_execution(char *input, t_env *envList, char **envp)
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
    tokens = ft_tokenize_input_with_strtok(input); // TODO rename this function
	//ft_initialize_commandList(command);    
	ft_parse_tokens(&first_command, tokens);
    ft_found_and_replace_usd(first_command, envList);
	if (first_command->next == NULL) // There is only one command (-> need to fork)
		ft_execute_cmd(first_command, envp, envList);
	else
	{
		ft_execute_cmds(first_command, envp, envList);
	}

	return 0;
}

//int	ft_launch_parsing_and_execution(t_commandList *commandList, \
	char *input, t_env *envList, char **envp)
// {
// 	t_command	*command;

//     command = NULL;
// 	if (commandList == NULL || input == NULL) {
//         perror("Error: Invalid pointer to commandList or null input in ft_launch_parsing_and_execution()\n");
//         return 1;
//     }
//     ft_initialize_commandList(commandList);
// 	if (!ft_check_quotes(input))
// 	{
// 		printf(">\n");
// 		return 0;
// 	}
// 	ft_remove_quotes(input);
// 	if (ft_tokenize_input_with_strtok(commandList, input) >= 1)
// 	{
// 		command = commandList->head;
// 		while (command != NULL)
// 		{
// 			ft_launch_redirection_execution(command);
// 			ft_launch_command_execution(command, commandList, envList, envp);
// 			command = command->next;
// 		}

// 	 	ft_destroy_commandList(commandList);
// 	}
// 	else
// 		perror("Hey, no token from input with strtok in ft_launch_parsing_and_execution.\n");
// 	return 0;
// }
