#include "minishell.h"

int ft_launch_parsing_and_execution(t_commandList *commandList, char *input, t_env *envList, char **envp) 
{
    t_command *command;

    ft_initialize_commandList(commandList);
	ft_check_if_input_is_tokenizable(commandList, input);
	ft_tokenize_input_with_strtok(commandList, input);

	command = commandList->head;
	while (command != NULL)
	{
		// TO DO : peut etre pas besoin de input dans ft_handle_pipes_execution() si info stockees dans structure?
		ft_handle_pipes_execution(input, command);
		ft_handle_command_execution(command, commandList, envList, envp);
		// TO DO : ft_handle_error() Ajoutez une gestion appropriée des erreurs, 
		// comme la vérification des permissions, la gestion des fichiers inexistants, etc.
		ft_handle_redirection_execution(input, command);
		command = command->next;
	}
    
	return 0;
}
