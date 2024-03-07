#include "minishell.h"

void	ft_command_add_back(t_command **commands, t_command *new_command)
{
	t_command	*current_command;

	current_command = *commands;
	if (*commands == NULL)
	{
		*commands = new_command;
		return ;
	}
	while (current_command->next != NULL)
	{
		current_command = current_command->next;
	}
	current_command->next = new_command;
}
