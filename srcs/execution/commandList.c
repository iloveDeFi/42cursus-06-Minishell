#include "minishell.h"

void	ft_initialize_commandList(t_commandList *commandList)
{
	if (commandList == NULL)
	{
		fprintf(stderr, "Error: NULL pointer in ft_init_commandList\n");
		exit(EXIT_FAILURE);
	}
	commandList->head = NULL;
	commandList->tail = NULL;
	commandList->length = 0;
}