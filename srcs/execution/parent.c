#include "minishell.h"

// // Redirect output to last pipe = receive last child process as an entree
void ft_configure_parent_process(t_command *command)
{
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
