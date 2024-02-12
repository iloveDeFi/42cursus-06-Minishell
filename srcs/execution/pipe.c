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

void ft_execute_piped_commands(t_command *command, int num_commands) 
{
    int i;

    i = 0; 
    while (i < num_commands - 1)
    {
        ft_create_pipes(command);
        i++;
    }

    ft_launch_child_processes(command);

    // Close file descriptors of pipes in the parent process
    ft_close_pipes(command);

    ft_wait_for_child_processes_to_end(command->child_pids, num_commands);
}
