#include "minishell.h"

void ft_configure_parent_process(t_command *command, int index, int number_of_pipes)
{
	// TO DO use number of pipes;
	(void)number_of_pipes;
    // Redirect output to last pipe
    if (index > 0)
    {
        if (dup2(command->pipes[index - 1][0], STDIN_FILENO) == -1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(command->pipes[index - 1][0]);
        close(command->pipes[index - 1][1]);
    }
}
