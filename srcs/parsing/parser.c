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
		// TO DO CHECK HEAD OR TAIL
        command = commandList->head;
		// TO DO ADD HANDLE REDIRECTION EXECUTION
		ft_handle_pipes_execution(input, command);
		ft_handle_command_execution(command, commandList, envList, envp);
    } 
    else 
    {
        perror("ft_parse_and_add_to_commandList failed. commandList problem.\n");
		g_exit_code = 1;
        return 1;
    }
	return 0;
}
