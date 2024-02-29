#include "minishell.h"

void	ft_initialize_child_processes(t_command *currentCommand)
{
	int i;

	i = 0;
	while (i < currentCommand->number_of_pipes + 1)
	{
		currentCommand->child_pids[i] = -1;
		i++;
	}
}

int ft_launch_child_processes(t_command *command) 
{
	int	i;

    i = 0;
    while (i < command->number_of_pipes + 1)
    {
        command->child_pids[i] = fork();
        if (command->child_pids[i] < 0)
        {
            perror("Error forking process while creating child process\n");
            exit(EXIT_FAILURE);
        }
        else if (command->child_pids[i] == 0)
        {
            ft_configure_child_process(command);
			ft_execute_child_process(command->args[0], command->args, command->envp);
        }
        i++;
    }
	return 0;
}

void ft_execute_child_process(char *full_path, char **args, char **envp)
{
    if (execve(full_path, args, envp) == -1) 
    {
        perror("Erreur lors de l'exécution de la commande");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

void ft_wait_for_all_child_processes_to_end(t_command *command) 
{
	int	i;

    i = 0;
    while (i < command->number_of_pipes + 1)
    {
        waitpid(command->child_pids[i], NULL, 0);
        i++;
    }
}

void ft_configure_child_process(t_command *command) 
{
    // Redirect input from previous pipe except for first command
    if (command->pipe_index > 0) {
        dup2(command->pipes[command->pipe_index - 1][0], STDIN_FILENO);
        close(command->pipes[command->pipe_index - 1][0]);
        close(command->pipes[command->pipe_index - 1][1]);
    }

    // Redirect output to next pipe
    if (command->pipe_index < command->number_of_pipes - 1) {
        dup2(command->pipes[command->pipe_index][1], STDOUT_FILENO);
        close(command->pipes[command->pipe_index][0]);
        close(command->pipes[command->pipe_index][1]);
    }
    ft_close_pipes(command);
}
