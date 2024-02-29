#include "minishell.h"

t_command	*ft_process_token(t_commandList *commandList, \
	t_command *currentCommand, char *token)
{
	if (commandList->length == 0)
		return (ft_process_first_token_as_command(commandList, token));
	else
	{
		if (ft_strcmp(currentCommand->name, "cd") == 0)
			ft_process_cd_argument(currentCommand, token);
		else
			ft_process_token_as_argument(commandList, currentCommand, token);
	}
	return (currentCommand);
}

t_command	*ft_process_first_token_as_command(t_commandList *commandList, \
	char *token)
{
	if (commandList == NULL || token == NULL)
		return (NULL);
	return (ft_create_init_new_command_commandlist(commandList, token));
}

void	ft_process_token_as_argument(t_commandList *commandList, \
	t_command *command, char *token)
{
	char	**newargs;

	if (command == NULL || token == NULL)
		return ;
	newargs = ft_allocate_and_copy_arguments(commandList, command->args, command->argCount, token);
	if (newargs == NULL)
	{
		free(command->name);
		free(command->args);
		return ;
	}
	free(command->args);
	command->args = newargs;
	command->argCount++;
}
