#include "minishell.h"

int ft_launch_parsing_and_execution(t_commandList *commandList, char *input, t_env *envList, char **envp) 
{
    t_command *command;

	if (commandList == NULL) {
        perror("Error: Invalid pointer to commandList in ft_launch_parsing_and_execution()\n");
        return -1; // Ou un code d'erreur approprié
    }
    ft_initialize_commandList(commandList);
	/*if (ft_check_if_input_is_tokenizable(commandList, input) != 0) 
	{
        perror("Error in ft_check_if_input_is_tokenizable\n");
        return -1; // TO DO : change g_exit_code value
    }*/
	if (!ft_check_quotes(input))
	{
		printf(">\n");
		return 0;
	}
    ft_remove_quotes(input);
    ft_tokenize_input_with_strtok(commandList, input);
	ft_found_and_replace_usd(commandList->head, envList);
	//ft_remove_quotes(input);
	command = commandList->head;
	while (command != NULL)
	{
		// TO DO : ft_handle_error() Ajoutez une gestion appropriée des erreurs,
		// comme la vérification des permissions, la gestion des fichiers inexistants, etc.
		ft_handle_pipes_execution(command); // TO DO : renvoie valeur erreur si fail
		ft_handle_command_execution(command, commandList, envList, envp); // TO DO : renvoie valeur erreur si fail
		//ft_handle_redirection_execution(command); // TO DO : renvoie valeur erreur si fail
		command = command->next;
	}
    
	return 0;
}