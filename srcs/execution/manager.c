#include "minishell.h"

// TO DO : ft_launch_parsing_and_execution where to use functions below
void ft_launch_error_manager(t_commandList *commandList, t_command *command, char *input, t_env *envList)
{

	if (!ft_check_quotes(input))
	{
		printf(">\n");
		return 0;
	}

	ft_remove_quotes(input);

	// TO DO : Make function below work
	//ft_found_and_replace_usd(commandList->head, envList);
	// if (ft_check_if_input_is_tokenizable(commandList, input) != 0) 
	// {
    //     perror("Error in ft_check_if_input_is_tokenizable\n");
    //     return -1; // TO DO : change g_exit_code value
    // }

	// TO DO check this function
	// ft_replace_env_variables_in_command(commandList->head, envList);
}