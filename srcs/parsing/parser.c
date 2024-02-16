#include "minishell.h"

int ft_launch_parsing_and_execution(t_commandList *commandList, char *input, t_env *envList, char **envp) 
{
	char *delimiters;
    t_command *command;

    ft_initialize_commandList(commandList);
	ft_check_if_input_is_tokenizable(commandList, input);
	delimiters = ft_change_strtok_delimiter(commandList, input);
	ft_tokenize_input_with_strtok(commandList, input, delimiters);

    if (commandList->head != NULL) 
    {	
        command = commandList->head;
		ft_handle_pipes_execution(input, command);
		ft_handle_command_execution();
       
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

int ft_handle_pipes_execution(char *input, t_command *command)
{
	if (ft_count_number_of_pipes(input) > 1)
    {
		if (ft_count_number_of_pipes(input) > MAX_COMMANDS)
			perror("Please do not use more than 10 pipes.\n");
        ft_execute_commands_with_pipe(command, (ft_count_number_of_pipes(input) + 1));
    }
}

int ft_handle_command_execution()
{
	ft_handle_command_execution();
}