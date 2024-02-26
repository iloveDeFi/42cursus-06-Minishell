#include "minishell.h"

// TO DO : Vous utilisez ft_execute_commands_with_pipe qui lance des processus enfants, 
// mais vous ne gérez pas explicitement la fermeture des descripteurs de fichiers dans le processus parent. 
// Assurez-vous de fermer les descripteurs de fichiers dans le processus parent après avoir terminé d'utiliser les pipes.

//Initialisez ou créez des pipes pour cette commande (pipe(currentCommand->pipes[currentCommand->pipe_index]
int ft_launch_pipe_execution(t_command *command)
{
	int read_fd;
	int write_fd;

	// // TO DO choose between MAX_COMMANDS and pipe_index
	// // Accéder au descripteur de fichier de lecture du pipe_index
	read_fd = command->pipes[command->pipe_index][0];
	// // Accéder au descripteur de fichier d'écriture du pipe_index;
	write_fd = command->pipes[command->pipe_index][1];
    ft_initialize_pipes(command);
    ft_launch_child_processes(command, command->number_of_pipes);
    ft_close_pipes(command, command->pipe_index, command->number_of_pipes);
	ft_wait_for_all_child_processes_to_end(command->child_pids, command->number_of_pipes);

    // Processus parent
    // Redirect output to last pipe
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
	return 0;
}