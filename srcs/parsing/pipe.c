#include "minishell.h"

void ft_initialize_pipes(t_command *currentCommand)
{
	printf("enter in ft_initialize_pipes\n");
    int i;

	i = 0;
    currentCommand->pipe_index = 0;

    while (i < currentCommand->number_of_pipes)
    {
        if (pipe(currentCommand->pipes[i]) == -1) 
        {
            perror("Erreur lors de la création des pipes dans ft_initialize_pipes\n");
            exit(EXIT_FAILURE);
        }
		currentCommand->pipe_index++;
		printf("Pipe_index is : %d\n", currentCommand->number_of_pipes);
        i++;
    }
}

int ft_count_number_of_pipes(char *input) 
{
	printf("enter in ft_count_number_of_pipe\n");
    int number_of_pipes;
	int i;

	i = 0;
	number_of_pipes = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '|' && input[i + 1] != '|')
			number_of_pipes += 1;
		i++;
	}
    return number_of_pipes;
}

void ft_close_pipes(t_command *command) 
{
	printf("enter in ft_close_pipes\n");
    int i;
	
	i = 0;
    while (i < command->number_of_pipes) 
	{
		// Hey, do not close the pipe used by the current process
		if (i != command->pipe_index)
		{
        	close(command->pipes[i][0]);
        	close(command->pipes[i][1]);
		}
        i++;
    }
}

// bool ft_check_if_pipe_in_char(char *token) 
// {
//     return (ft_strcmp(token, "|") == 0);
// }

// bool ft_check_if_pipe_in_string(char *token) 
// {
//     return (strstr(token, "|") != NULL);
// }

// int ft_check_if_pipe_in_inputCopy(char *inputCopy) 
// {
//     return (ft_strchr(inputCopy, '|') != NULL);
// }

// int ft_check_too_many_pipes()
// {
// 	if (ft_count_number_of_pipes(command->name) > 1)
//     {
// 		if (ft_count_number_of_pipes(command->name) > MAX_COMMANDS)
// 		{
// 			perror("Please do not use more than 10 pipes.\n");
// 			g_exit_code = ERROR_TOO_MANY_PIPES;
// 		}
// 	}
// }
