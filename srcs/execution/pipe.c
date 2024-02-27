#include "minishell.h"

// TO DO :
// Assurez-vous de fermer les descripteurs de fichiers dans le processus parent après avoir terminé d'utiliser les pipes.

void ft_launch_pipe_execution(t_command *command)
{
    printf("enter in ft_launch_pipe_execution\n");
    int read_fd;
    int write_fd;

    // Accéder au descripteur de fichier de lecture du pipe_index
    read_fd = command->pipes[command->pipe_index][0];
    // Accéder au descripteur de fichier d'écriture du pipe_index
    write_fd = command->pipes[command->pipe_index][1];

    ft_initialize_pipes(command);
    ft_launch_child_processes(command, command->number_of_pipes);
    ft_close_pipes(command, command->pipe_index, command->number_of_pipes);
    ft_wait_for_all_child_processes_to_end(command->child_pids, command->number_of_pipes);

    // Processus parent
    ft_configure_parent_process(command, command->pipe_index, command->number_of_pipes);

    // Exécuter la dernière commande
    pid_t child_pid = fork();

    if (child_pid < 0)
    {
        perror("Error forking process while executing last command\n");
        exit(EXIT_FAILURE);
    }
    else if (child_pid == 0)
    {
        // Processus fils
        ft_configure_child_process(command, command->pipe_index, command->number_of_pipes);
        execve(command->args[0], command->args, command->envp);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else
    {
        // Processus parent
        waitpid(child_pid, NULL, 0);
    }
}
