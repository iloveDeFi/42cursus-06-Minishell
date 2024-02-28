#include "minishell.h"

// TO DO : where used ?
void	ft_initialize_child_processes(t_command *currentCommand)
{
	int i;

	i = 0;
	// Ex. 3 pipes means 4 child processess
	while (i < currentCommand->number_of_pipes + 1)
	{
		// PID invalid by defaut
		currentCommand->child_pids[i] = -1;
		i++;
	}
}

pid_t ft_create_child_process(t_command *command) 
{
    int i;

	i = 0;

	while (command->child_pids[i] < currentCommand->number_of_pipes + 1)
	{
		command->child_pids[i] = fork();
		if (command->child_pids[i] < 0)
		{
        	perror("Error forking process while creating child process\n");
        	exit(EXIT_FAILURE);
    	}
		return command->child_pids[i];
	}
}

void ft_launch_child_processes(t_command *command) 
{
    int i;
	
	i = 0;
    while (i < command->number_of_pipes) 
	{
        command->child_pids[i] = ft_create_child_process(command);
		if (command->child_pids[i] < 0) 
		{
            perror("fork error in ft_launch_child_processes\n");
            exit(EXIT_FAILURE);
		}
        else if (command->child_pids[i] == 0) 
		{
            ft_configure_child_process(command);
			// TO DO : exec pipe here ?
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
    // Rediriger l'entrée depuis le pipe précédent car pas le premier dans la chaine des pipes
    if (command->pipe_index > 0) {
        dup2(command->pipes[command->pipe_index - 1][0], STDIN_FILENO);
        close(command->pipes[command->pipe_index - 1][0]);
        close(command->pipes[command->pipe_index - 1][1]);
    }

    // Rediriger la sortie vers le pipe suivant
    if (command->pipe_index < command->number_of_pipes - 1) {
        dup2(command->pipes[command->pipe_index + 1][1], STDOUT_FILENO);
        close(command->pipes[command->pipe_index + 1][0]);
        close(command->pipes[command->pipe_index + 1][1]);
    }
    ft_close_pipes(command);
}