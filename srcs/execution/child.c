#include "minishell.h"

pid_t ft_create_child_process() 
{
    pid_t child_pid;
    
    child_pid = fork();

    if (child_pid < 0) {
        perror("Error forking process while creting child process\n");
        exit(EXIT_FAILURE);
    }

    return child_pid;
}

void ft_launch_child_processes(t_command *data) 
{
    int i = 0;

    while (i < MAX_COMMANDS) {
        data->child_pids[i] = ft_create_child_process();

        if (data->child_pids[i] == 0) {
            // Processus enfant
            ft_configure_child_process(data, i);
            exit(EXIT_SUCCESS);
        }

        i++;
    }
}

void ft_execute_child_process(char *full_path, char **args, char **envp)
 {
    if (execve(full_path, args, envp) == -1) 
    {
        perror("Erreur lors de l'exécution de la commande");
        exit(EXIT_FAILURE);
    }
}

void ft_wait_for_child_processes_to_end(pid_t *child_pids, int num_commands) 
{
    int i;

    i = 0;
    while (i < num_commands)
    {
        waitpid(child_pids[i], NULL, 0);
        i++;
    }
}

// void ft_wait_for_child_processes_to_end(pid_t *child_pids, int num_commands) 
// {
//     int i;

//     i = 0;
//     while (i < num_commands)
//     {
//         ft_wait_for_child_process(child_pids[i]);
//         i++;
//     }
// }

void ft_configure_child_process(t_command *data, int index) 
{
    if (index > 0) {
        // Rediriger l'entrée depuis le pipe précédent
        dup2(data->pipes[index - 1][0], STDIN_FILENO);
    }

    if (index < MAX_COMMANDS - 1) {
        // Rediriger la sortie vers le pipe suivant
        dup2(data->pipes[index][1], STDOUT_FILENO);
    }

    // Fermer tous les descripteurs de fichiers des pipes
    ft_close_pipes(data);

    // Exécuter la commande avec pipe
    ft_execute_commands_with_pipe(data);
}

