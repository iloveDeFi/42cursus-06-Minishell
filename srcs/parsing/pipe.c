#include "minishell.h"

// Pipes are init in t_command node initialization, then we create them here BEFORE execution
void ft_create_pipes(t_command *command)
{
    int pipe_index;
	
	pipe_index = command->pipe_index;

    if (pipe(command->pipes[pipe_index]) == -1) 
    {
        perror("Error creating pipe");
        exit(EXIT_FAILURE);
    }
}

int ft_count_number_of_pipes(char *input) 
{
    int number_of_pipes;
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


void ft_close_pipes(t_command *command) 
{
    int i;
	
	i = 0;
    while (i < number_of_pipes) 
	{
		if (i != index)
		{
        	close(command->pipes[i][0]);
        	close(command->pipes[i][1]);
		}
        i++;
    }
}

bool ft_check_if_pipe_in_char(char *token) 
{
    return (ft_strcmp(token, "|") == 0);
}

bool ft_check_if_pipe_in_string(char *token) 
{
    return (strstr(token, "|") != NULL);
}

int ft_check_if_pipe_in_inputCopy(char *inputCopy) 
{
    return (ft_strchr(inputCopy, '|') != NULL);
}

// int ft_check_too_many_piipes()
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