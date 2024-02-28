#include "minishell.h"

// TO DO :
// Assurez-vous de fermer les descripteurs de fichiers dans le processus parent après avoir terminé d'utiliser les pipes.

void ft_launch_pipe_execution(t_command *command)
{
    printf("enter in ft_launch_pipe_execution\n");
    
    ft_initialize_pipes(command);
    ft_launch_child_processes(command);
    ft_close_pipes(command);
    ft_wait_for_all_child_processes_to_end(command);

    // Processus parent
    ft_configure_parent_process(command);
}
