#include "minishell.h"

void ft_configure_parent_process(t_command *command)
{
	// TO DO use number of pipes ?
	// command->number_of_pipes;
    // Redirect output to last pipe
    if (command->pipe_index > 0)
    {
        if (dup2(command->pipes[command->pipe_index - 1][0], STDIN_FILENO) == -1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(command->pipes[command->pipe_index - 1][0]);
        close(command->pipes[command->pipe_index - 1][1]);
    }
}
