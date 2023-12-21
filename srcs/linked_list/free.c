#include "minishell.h"

void ft_free_list(t_commandList  *head)
{
    t_command  *current = head->head;
    
    while (current != NULL)
    {
        t_command  *next = current->next;
        free(current->data);
        free(current);

        current = next;
    }
}

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

void ft_free_node(t_command  *node)
{
    if (node != NULL)
    {
        free(node->data);

        if (node->prev != NULL)
            node->prev->next = node->next;
            
        if (node->next != NULL)
            node->next->prev = node->prev;

        free(node);
    }
}

void    ft_free_env_node(t_env *new_node, t_env *tmp, char *str)
{
	free(tmp->value);
	tmp->value = ft_strdup(str);
	free(new_node->var);
	free(new_node->value);
	free(new_node);
}
