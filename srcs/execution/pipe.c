#include "minishell.h"

void ft_launch_pipe_execution(t_command *command)
{
    printf("enter in ft_launch_pipe_execution\n");

    ft_initialize_pipes(command);
    ft_initialize_child_processes(command);
    //ft_launch_redirection_execution(command);
    //ft_launch_child_processes(command);
    //ft_close_pipes(command);
    ft_wait_for_all_child_processes_to_end_pipe(command);
    ft_configure_parent_process(command);
}

void ft_wait_for_all_child_processes_to_end_pipe(t_command *command) {
    printf("wait for all child PIPE process\n");
    int i;

    for (i = 0; i < command->num_child_processes; i++) { // Attendre seulement les processus liés aux pipes
        waitpid(command->child_pids[i], NULL, 0);
    }
}