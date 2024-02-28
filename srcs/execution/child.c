#include "minishell.h"

void	ft_initialize_child_processes(t_command *currentCommand)
{
	int i;

	i = 0;
	while (i < MAX_COMMANDS)
	{
		// PID invalid by defaut
		currentCommand->child_pids[i] = -1;
		i++;
	}
}

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

void ft_launch_child_processes(t_command *command) 
{
    int i = 0;

    while (i < command->number_of_pipes) 
	{
        command->child_pids[i] = ft_create_child_process(/*command, i*/);
		if (command->child_pids[i] < 0) 
		{
            perror("fork error in ft_launch_child_processes\n");
            exit(EXIT_FAILURE);
		}
		// Child process
        else if (command->child_pids[i] == 0) 
		{
            ft_configure_child_process(command);
            ft_launch_pipe_execution(command);
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

// TO DO : Gestion des processus : Dans ft_wait_for_all_child_processes_to_end, 
// assurez-vous de boucler correctement pour attendre tous les processus enfants. 
// Vous utilisez actuellement waitpid avec un seul PID, mais dans le cas des pipes, 
// vous devrez attendre tous les processus enfants.
void ft_wait_for_all_child_processes_to_end(t_command *command) 
{
    int i;

    i = 0;
    while (i < command->number_of_pipes)
    {
        waitpid(command->child_pids[i], NULL, 0);
        i++;
    }
}

void ft_configure_child_process(t_command *command) 
{
    // Rediriger l'entrée depuis le pipe précédent
    if (command->pipe_index > 0) {
        dup2(command->pipes[command->pipe_index - 1][0], STDIN_FILENO);
        close(command->pipes[command->pipe_index - 1][0]);
        close(command->pipes[command->pipe_index - 1][1]);
    }

    // Rediriger la sortie vers le pipe suivant
    if (command->pipe_index < command->number_of_pipes - 1) {
        dup2(command->pipes[command->pipe_index][1], STDOUT_FILENO);
        close(command->pipes[command->pipe_index][0]);
        close(command->pipes[command->pipe_index][1]);
    }

    // Fermer tous les descripteurs de fichiers des pipes
    ft_close_pipes(command);
}