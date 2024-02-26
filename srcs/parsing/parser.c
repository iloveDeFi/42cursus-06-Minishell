#include "minishell.h"

int ft_launch_parsing_and_execution(t_commandList *commandList, char *input, t_env *envList, char **envp) 
{
    t_command *command;

	if (commandList == NULL) {
        perror("Error: Invalid pointer to commandList in ft_launch_parsing_and_execution()\n");
        return 1;
    }
	
    ft_initialize_commandList(&commandList);

	// if (ft_check_if_input_is_tokenizable(commandList, input) != 0) 
	// {
    //     perror("Error in ft_check_if_input_is_tokenizable\n");
    //     return -1; // TO DO : change g_exit_code value
    // }
	
	if (ft_tokenize_input_with_strtok(&commandList, input) > 1)
	{
		// TO DO check this function
		// ft_replace_env_variables_in_command(commandList->head, envList);

		command = commandList->head;
		while (command != NULL)
		{
			// ft_handle_error(); TO DO SOON
			ft_pipe_execution(commandList, command);
			ft_redirection_execution(commandList, command);
			ft_command_execution(commandList, command, envList, envp);
			command = command->next;
		}

	 	ft_destroy_commandList(commandList);
		return 0;
	}
		else
			perror("Hey, no token from input with strtok.\n");
}
