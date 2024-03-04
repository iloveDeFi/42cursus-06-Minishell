#include "minishell.h"

void	ft_initialize_child_processes(t_command *currentCommand)
{
    printf("initialise child process\n");
	int i;

	i = 0;
	while (i < currentCommand->number_of_pipes + 1)
	{
		currentCommand->child_pids[i] = -1;
		i++;
	}
    printf("Number of child pids created: %d\n", i);
}

/* int ft_launch_child_processes(t_command *command) 
{
    (printf("child process\n"));
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
			//ft_execute_child_process(command->args[0], command->args, NULL);
        }
        i++;
    }
    printf("Child PIDs: ");
    for (int j = 0; j < command->number_of_pipes + 1; j++) {
        printf("%d ", command->child_pids[j]);
    }
    printf("\n");
	return 0;
} */

int ft_launch_child_processes(t_command *command) {
    printf("child process\n");
    int i;

    command->num_child_processes = 0; // Initialiser le nombre de processus fils liés aux pipes à 0

    for (i = 0; i < command->number_of_pipes + 1; i++)
    {
        command->child_pids[i] = fork();
        if (command->child_pids[i] < 0) {
            perror("Error forking process while creating child process\n");
            exit(EXIT_FAILURE);
        } else if (command->child_pids[i] == 0) {
            // Child process
            ft_configure_child_process(command);
            // Execute the command
            execvp(command->args[0], command->args);
            // If execvp returns, it must have failed
            perror("Error executing command");
            exit(EXIT_FAILURE);
        }
        else
        {
            // Parent process
            command->num_child_processes++; // Incrémenter le nombre de processus fils liés aux pipes
        }
    }
    // Parent process continues here
    return 0;
}




void ft_execute_child_process(char *full_path, char **args, char **envp)
{
    printf("execute child process\n");
    if (execve(full_path, args, envp) == -1) 
    {
        perror("aiiiie Erreur lors de l'exécution de la commande");
        exit(EXIT_FAILURE);
    }
}

void ft_wait_for_all_child_processes_to_end(t_command *command) 
{
	printf("wait for all child process\n");
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
    printf("enter configure child process\n");
    // Redirect input from previous pipe except for first command
    if (command->pipe_index > 0) {
        printf("Redirecting input from pipe %d\n", command->pipe_index - 1);
        dup2(command->pipes[command->pipe_index - 1][0], STDIN_FILENO);
        close(command->pipes[command->pipe_index - 1][0]);
        close(command->pipes[command->pipe_index - 1][1]);
    }

    // Redirect output to next pipe
    if (command->pipe_index < command->number_of_pipes) {
        printf("Redirecting input from pipe %d\n", command->pipe_index - 1);
        dup2(command->pipes[command->pipe_index][1], STDOUT_FILENO);
        close(command->pipes[command->pipe_index][0]);
        close(command->pipes[command->pipe_index][1]);
    }
    //ft_close_pipes(command);
} 

/* void ft_configure_child_process(t_command *command) 
{
    printf("enter configure child process\n");

    // Redirect input from previous pipe except for first command
    if (command->pipe_index > 0 && command->pipe_index <= command->number_of_pipes) {
        printf("Redirecting input from pipe %d\n", command->pipe_index - 1);
        dup2(command->pipes[command->pipe_index - 1][0], STDIN_FILENO);
        close(command->pipes[command->pipe_index - 1][0]);
        close(command->pipes[command->pipe_index - 1][1]);
    }

    // Redirect output to next pipe
    if (command->pipe_index < command->number_of_pipes) {
        printf("Redirecting output to pipe %d\n", command->pipe_index);
        dup2(command->pipes[command->pipe_index][1], STDOUT_FILENO);
        close(command->pipes[command->pipe_index][0]);
        close(command->pipes[command->pipe_index][1]);
    }
    //ft_close_pipes(command);
} */


