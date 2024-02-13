#include "minishell.h"

void ft_execute_commands_with_pipe(t_command *data) 
{
	int i;
    ft_create_pipes(data);
    ft_create_child_process();

	i = 0;
    if (data->child_pids[i] == 0) {
        // Child process code
        close(data->pipes[data->pipe_index][1]);  // Close unused write end of the pipe
        dup2(data->pipes[data->pipe_index][0], STDIN_FILENO);  // Redirect standard input to the pipe
        close(data->pipes[data->pipe_index][0]);  // Close the file descriptor
        ft_execute_commands_with_pipe(data);
    } else {
        // Parent process code
        close(data->pipes[data->pipe_index][0]);  // Close unused read end of the pipe
        dup2(data->pipes[data->pipe_index][1], STDOUT_FILENO);  // Redirect standard output to the pipe
        close(data->pipes[data->pipe_index][1]);  // Close the file descriptor
        execvp(data->args[0], data->args);  // Execute the command
        perror("execvp");
        exit(EXIT_FAILURE);
    }
}

void ft_execute_piped_commands(t_command *command, int number_of_pipes) 
{
    int i;

    i = 0; 
    while (i < number_of_pipes - 1)
    {
        ft_create_pipes(command);
		command->pipe_index++;
        i++;
    }

    ft_launch_child_processes(command, number_of_pipes);

    // Close file descriptors of pipes in the parent process
    ft_close_pipes(command, number_of_pipes);

    ft_wait_for_child_processes_to_end(command->child_pids, number_of_pipes);
}

void ft_process_sub_input_as_command(t_commandList *commandList, char *subInput) 
{
    char *token;
    char subInputCopy[ft_strlen(subInput) + 1];
    char *delimiters;
	
	delimiters = " ";
    ft_strcpy(subInputCopy, subInput);
    
    // Traiter le premier token comme une commande
    token = ft_strtok(subInputCopy, delimiters);
    ft_process_the_first_token_as_a_command(commandList, token);

    // Traiter les tokens suivants comme des arguments
    while ((token = ft_strtok(NULL, delimiters)) != NULL) 
    {
        ft_process_token_as_an_argument(commandList, commandList->tail, token);
    }
}