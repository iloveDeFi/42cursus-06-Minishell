#include "minishell.h"

int ft_launch_parsing_and_execution(t_commandList *commandList, char *input, t_env *envList, char **envp) 
{
    t_command *command;

    command = NULL;
	if (commandList == NULL || input == NULL) {
        perror("Error: Invalid pointer to commandList or null input in ft_launch_parsing_and_execution()\n");
        return 1;
    }
    ft_initialize_commandList(commandList);
	// TO DO : custom error manager
	// ft_launch_error_manager(commandList, command, input, envList);

	if (ft_tokenize_input_with_strtok(commandList, input) >= 1)
	{
		command = commandList->head;
		while (command != NULL)
		{
			// ft_launch_pipe_execution(command);
			ft_launch_redirection_execution(command);
			ft_launch_command_execution(command, commandList, envList, envp);
			command = command->next;
		}

	 	ft_destroy_commandList(commandList);
	}
	else
		perror("Hey, no token from input with strtok in ft_launch_parsing_and_execution.\n");
	return 0;
}
