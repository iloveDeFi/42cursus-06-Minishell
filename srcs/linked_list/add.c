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
