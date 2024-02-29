#include "minishell.h"

int	ft_launch_parsing_and_execution(t_commandList *commandList, \
	char *input, t_env *envList, char **envp)
{
	t_command	*command;

	if (commandList == NULL)
	{
		perror("Error: Invalid pointer to commandList in \
			ft_launch_parsing_and_execution()\n");
		return (-1);
	}
	ft_initialize_commandlist(commandList);
	if (!ft_check_quotes(input))
	{
		printf(">\n");
		return (0);
	}
	ft_remove_quotes(input);
	ft_tokenize_input_with_strtok(commandList, input);
	ft_found_and_replace_usd(commandList->head, envList);
	command = commandList->head;
	while (command != NULL)
	{
		ft_handle_pipes_execution(command);
		ft_handle_command_execution(command, commandList, envList, envp);
		command = command->next;
	}
	return (0);
}
