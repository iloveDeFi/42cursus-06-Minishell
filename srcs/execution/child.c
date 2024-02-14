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

void ft_launch_child_processes(t_command *command, int number_of_pipes) 
{
    int i = 0;

    while (i < number_of_pipes) 
	{
        command->child_pids[i] = ft_create_child_process(/*command, i*/);
		if (command->child_pids[i] < 0) 
		{
            perror("fork error in ft_launch_child_processes\n");
            exit(EXIT_FAILURE);
		}
        else if (command->child_pids[i] == 0) {
            // Processus enfant
            ft_configure_child_process(command, i, number_of_pipes);
            ft_execute_commands_with_pipe(command, number_of_pipes);
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

void ft_wait_for_child_processes_to_end(pid_t *child_pids, int number_of_pipes) 
{
    int i;

    i = 0;
    while (i < number_of_pipes)
    {
        waitpid(child_pids[i], NULL, 0);
        i++;
    }
}

void ft_configure_child_process(t_command *command, int index, int number_of_pipes) 
{
    // Rediriger l'entrée depuis le pipe précédent
    if (index > 0) {
        dup2(command->pipes[index - 1][0], STDIN_FILENO);
        close(command->pipes[index - 1][0]);
        close(command->pipes[index - 1][1]);
    }

    // Rediriger la sortie vers le pipe suivant
    if (index < number_of_pipes - 1) {
        dup2(command->pipes[index][1], STDOUT_FILENO);
        close(command->pipes[index][0]);
        close(command->pipes[index][1]);
    }

    // Fermer tous les descripteurs de fichiers des pipes
    ft_close_pipes(command, index, number_of_pipes);
}