#include "minishell.h"

void ft_create_pipes(t_command *command)
{
    int pipe_index;
	
	pipe_index = command->execution_data->pipe_index;

    if (pipe(command->execution_data->pipes[pipe_index]) == -1) 
    {
        perror("Error creating pipe");
        exit(EXIT_FAILURE);
    }
	// Fermeture de l'extrémité de lecture inutilisée du pipe
    close(command->execution_data->pipes[pipe_index][0]);
}

void ft_create_pipes_array(int pipes[][2], int num_pipes) 
{
    int i;
    
    i = 0;
    while (i < num_pipes)
    {
        if (pipe(pipes[i]) == -1) 
        {
            perror("Error creating pipe");
            exit(EXIT_FAILURE);
        }
        i++;
    }
}

int ft_count_piped_commands(t_command *start_command) 
{
    int number_of_pipes; // Initialisation à 0, car aucune pipe n'a encore été rencontrée
    t_command *current_command;

	int number_of_pipes = 0;
	t_command *current_command = start_command;
    while (current_command->next != NULL) 
    {
        if (ft_stop_token_with_pipe_from_commandList(current_command->name)) // Utilisation de la fonction dédiée
            number_of_pipes++;

        current_command = current_command->next;
    }
    return number_of_pipes;
}


void ft_close_pipes(t_execution_data *data) 
{
    int i;
	
	i = 0;
    while (i < MAX_COMMANDS - 1) {
        close(data->pipes[i][0]);
        close(data->pipes[i][1]);
        i++;
    }
}

bool ft_stop_token_with_pipe_from_commandList(char *token) 
{
    return (ft_strcmp(token, "|") == 0);
}

int ft_check_if_pipe_in_input(char *inputCopy) 
{
    return (strchr(inputCopy, '|') != NULL);
}