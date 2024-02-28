#include "minishell.h"

// TO DO :
// Assurez-vous de fermer les descripteurs de fichiers dans le processus parent après avoir terminé d'utiliser les pipes.

void ft_launch_pipe_execution(t_command *command)
{
    printf("enter in ft_launch_pipe_execution\n");
    int read_fd;
    int write_fd;
	pid_t child_pid;

    read_fd = command->pipes[command->pipe_index][0];
    write_fd = command->pipes[command->pipe_index][1];
    ft_initialize_pipes(command);
    ft_launch_child_processes(command);
    ft_close_pipes(command);
    ft_wait_for_all_child_processes_to_end(command);

    // Processus parent
    ft_configure_parent_process(command);

    // Exécuter la dernière commande
    child_pid = fork();

    if (child_pid < 0)
    {
        perror("Error forking process while executing last command\n");
        exit(EXIT_FAILURE);
    }
    else if (child_pid == 0)
    {
        // Processus fils
        ft_configure_child_process(command);
        execve(command->args[0], command->args, command->envp);
        perror("execve in ft_launch_pipe_execution\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        // Processus parent
        waitpid(child_pid, NULL, 0);
    }
}
