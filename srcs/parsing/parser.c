#include "minishell.h"

int ft_split_input_in_token_with_delimiter(t_commandList *commandList, char *input) 
{
    char *delimiters = " ";

    if (ft_check_if_pipe_in_string(input))
    {
        delimiters = " |";
    }

    return ft_process_input_with_strtok(commandList, input, delimiters);
}


int ft_check_if_input_is_tokenizable(t_commandList *commandList, char *input) 
{
    if (commandList == NULL)
    {
        perror("commandList head is NULL in ft_check_if_input_is_tokenizable");
        return 1;
    }
    if (ft_split_input_in_token_with_delimiter(commandList, input) > 0) 
    {
        return 0;
    } 
    else 
    {
        perror("Parsing failed in ft_check_if_input_is_tokenizable");
        ft_destroy_command(commandList);
        return 1;
    }
}

int ft_launch_parsing_and_execution(t_commandList *commandList, char *input, t_env *envList, char **envp) 
{
    t_command *command;

    ft_initialize_commandList(commandList);

    if (ft_check_if_input_is_tokenizable(commandList, input) == 0 && commandList->head != NULL) 
    {	
        command = commandList->head;
        if (ft_count_number_of_pipes(input) > 1)
        {
			if (ft_count_number_of_pipes(input) > MAX_COMMANDS)
				perror("Please do not use more than 10 pipes.\n");
            ft_execute_commands_with_pipe(command, (ft_count_number_of_pipes(input) + 1));
        }
        else if (ft_execute_single_command(command, commandList, envList, envp) != 0) 
        {
            perror("Error executing command\n");
            ft_destroy_command(commandList);
            return 1;
        }
        return 0;
    } 
    else 
    {
        perror("ft_parse_and_add_to_commandList failed. commandList problem.\n");
        return 1;
    }
}
