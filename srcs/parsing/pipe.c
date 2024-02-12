#include "minishell.h"

void ft_create_pipes(t_command *command)
{
    int pipe_index;
	
	pipe_index = command->pipe_index;

    if (pipe(command->pipes[pipe_index]) == -1) 
    {
        perror("Error creating pipe");
        exit(EXIT_FAILURE);
    }
	// Fermeture de l'extrémité de lecture inutilisée du pipe
    close(command->pipes[pipe_index][0]);
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

int ft_count_number_of_pipes(char *input) 
{
    int number_of_pipes; // Initialisation à 0, car aucune pipe n'a encore été rencontrée
	int i;

	i = 0;
	number_of_pipes = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '|')
			number_of_pipes += 1;
		i++;
	}
    return number_of_pipes;
}


void ft_close_pipes(t_command *data) 
{
    int i;
	
	i = 0;
    while (i < MAX_COMMANDS - 1) {
        close(data->pipes[i][0]);
        close(data->pipes[i][1]);
        i++;
    }
}

bool ft_check_if_pipe_in_char(char *token) 
{
    return (ft_strcmp(token, "|") == 0);
}

// TO DO HARDCODE STRSTR
bool ft_check_if_pipe_in_string(char *token) 
{
    return (strstr(token, "|") != NULL);
}

int ft_check_if_pipe_in_inputCopy(char *inputCopy) 
{
    return (ft_strchr(inputCopy, '|') != NULL);
}