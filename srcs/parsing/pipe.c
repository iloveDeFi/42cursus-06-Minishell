#include "minishell.h"

void ft_create_pipes(t_command *command->pipe_fd[2])
{
    if (pipe(command->pipe_fd[2]) == -1) 
    {
        perror("Error creating pipe");
        exit(EXIT_FAILURE);
    }
}

void ft_create_pipes_array(int pipes[][2], int num_pipes) 
{
    int i;
    
    i = 0;
    while (i < num_pipes)
    {
        ft_create_pipes(pipes[i]);
        i++;
    }
}


int ft_count_piped_commands(t_command *start_command) 
{
    int num_commands;
    t_command *current_command;
    
    num_commands = 1;
    current_command = start_command;

    while (current_command->next != NULL && current_command->next->tokenType == PIPE) 
    {
        num_commands++;
        current_command = current_command->next;
    }
	return num_commands;
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