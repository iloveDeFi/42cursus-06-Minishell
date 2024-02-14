#include "minishell.h"

void ft_execute_commands_with_pipe(t_command *command, int number_of_pipes)
{
    if (number_of_pipes > 0) {
        ft_create_pipes(command);
        ft_launch_child_processes(command, number_of_pipes);
        ft_close_pipes(command, command->pipe_index, number_of_pipes);
    }

    // Processus parent
    // Rediriger la sortie vers le dernier pipe
    if (command->pipe_index > 0) {
        dup2(command->pipes[command->pipe_index - 1][0], STDIN_FILENO);
        close(command->pipes[command->pipe_index - 1][0]);
        close(command->pipes[command->pipe_index - 1][1]);
    }

    // Exécuter la dernière commande
    execvp(command->args[0], command->args);
    perror("execvp");
    exit(EXIT_FAILURE);
}