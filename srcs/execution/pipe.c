#include "minishell.h"

void ft_execute_commands_with_pipe(t_execution_data *data) 
{
    ft_create_pipes(data->commands->pipe_fd);
    ft_create_child_process();

    if (data->commands->child_pid == 0) {
        // Code du processus enfant
        close(data->commands->pipe_fd[1]);  // Fermeture de l'extrémité d'écriture inutilisée du pipe
        dup2(data->commands->pipe_fd[0], STDIN_FILENO);  // Redirection de l'entrée standard vers le pipe
        close(data->commands->pipe_fd[0]);  // Fermeture du descripteur de fichier inutile
        ft_execute_commands_with_pipe(data);
    } else {
        // Code du processus parent
        close(data->commands->pipe_fd[0]);  // Fermeture de l'extrémité de lecture inutilisée du pipe
        dup2(data->commands->pipe_fd[1], STDOUT_FILENO);  // Redirection de la sortie standard vers le pipe
        close(data->commands->pipe_fd[1]);  // Fermeture du descripteur de fichier inutile
        execvp(data->commands->args[0], data->commands->args);  // Exécution de la commande
        perror("execvp");
        exit(EXIT_FAILURE);
    }
}

void ft_execute_piped_commands(t_commandList *commandList, t_command *commands, t_env *envList, char **envp) 
{
	int i;
    t_execution_data data;
    data.commands = commands;
    data.envList = envList;
    data.envp = envp;

    int num_commands = ft_count_piped_commands(commands);

    // Créer les pipes
    i= 0; 
	while (i < num_commands - 1)
	{
		ft_create_pipes(data.pipes[i]);
		i++;
	}
    // Lancer les processus enfants
    ft_launch_child_processes(&data);

    // Fermer les descripteurs de fichiers des pipes dans le processus parent
    ft_close_pipes(&data);

    // Attendre que tous les processus enfants se terminent
    ft_wait_for_child_processes_to_end(&data);
}
