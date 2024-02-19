#include "minishell.h"

int ft_handle_pipes_execution(t_command *command)
{
	if (ft_count_number_of_pipes(command->name) > 1)
    {
		if (ft_count_number_of_pipes(command->name) > MAX_COMMANDS)
			perror("Please do not use more than 10 pipes.\n");
        ft_execute_commands_with_pipe(command, (ft_count_number_of_pipes(command->name) + 1));
    }
	return 0;
}

// TO DO : Vous utilisez ft_execute_commands_with_pipe qui lance des processus enfants, 
// mais vous ne gérez pas explicitement la fermeture des descripteurs de fichiers dans le processus parent. 
// Assurez-vous de fermer les descripteurs de fichiers dans le processus parent après avoir terminé d'utiliser les pipes.
void ft_execute_commands_with_pipe(t_command *command, int number_of_pipes)
{
    if (number_of_pipes > 0) 
	{
        ft_create_pipes(command);
        ft_launch_child_processes(command, number_of_pipes);
        ft_close_pipes(command, command->pipe_index, number_of_pipes);
		ft_wait_for_all_child_processes_to_end(command->child_pids, number_of_pipes);

    }
    // Processus parent
    // Rediriger la sortie vers le dernier pipe
    if (command->pipe_index > 0) 
	{
		if (dup2(command->pipes[command->pipe_index - 1][0], STDIN_FILENO) == -1) 
		{
    		perror("dup2");
    		exit(EXIT_FAILURE);
		}
        close(command->pipes[command->pipe_index - 1][0]);
        close(command->pipes[command->pipe_index - 1][1]);
    }

    // Exécuter la dernière commande
    execvp(command->args[0], command->args);
    perror("execvp");
    exit(EXIT_FAILURE);
}