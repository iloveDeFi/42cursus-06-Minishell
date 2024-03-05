#include "minishell.h"

void	ft_add_to_list(t_env **envList, t_env *new_node)
{
	t_env	*current;

	if (envList == NULL || new_node == NULL)
		return ;
	if (*envList == NULL)
	{
		*envList = new_node;
	}
	else
	{
		current = *envList;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
		new_node->prev = current;
	}
}

// void	ft_append_to_commandlist(t_commandList *commandList, t_command *newNode)
// {
// 	if (commandList == NULL || newNode == NULL)
// 	{
// 		perror("ft_append_to_list: Invalid commandList or newCommand.\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	newNode->next = NULL;
// 	if (commandList->head == NULL)
// 	{
// 		commandList->head = newNode;
// 		commandList->tail = newNode;
// 	}
// 	else
// 	{
// 		commandList->tail = newNode;
// 		commandList->tail->next = NULL;
// 	}
// 	commandList->length++;
// }
