#include "minishell.h"

void	ft_initialize_commandlist(t_commandList *commandList)
{
	if (commandList == NULL)
	{
		fprintf(stderr, "Error: NULL pointer in ft_init_commandList\n");
		exit(EXIT_FAILURE);
	}
	commandList->head = NULL;
	commandList->tail = NULL;
	commandList->length = 0;
	printf("commandlist ok\n");
}

/* void	ft_print_commandlist(t_commandList *commandList)
{
	int			i;
	t_command	*current;

	if (commandList == NULL || commandList->head == NULL)
		return ;
	current = commandList->head;
	while (current != NULL)
	{
		printf("Command: %s\n", current->name);
		i = 0;
		while (i < current->argCount)
		{
			printf("Argument %d: %s\n", i, current->args[i]);
			i++;
		}
		current = current->next;
	}
} */
