#include "minishell.h"

t_command  *ft_get_previous_node(t_commandList  *head, t_command  *node)
{
    t_command *current = head->head;
    t_command  *previous = NULL;
    while (current != NULL)
    {
        if(current == node)
            return previous;
        previous = current;
        current = current->next;
    }
    return NULL;
}

t_command  *ft_find_node(t_commandList  *head, void *target)
{
    t_command  *current = head->head;
    while (current != NULL)
    {
        if (ft_compareString(current->data, target) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

/* void    *ft_get_last_element_in_list(t_commandList *head)
{
	if (head == NULL)
        return NULL;
    t_command *current = head->head;
    while (current->next != NULL)
        current = current->next;
    return current->data;
}*/

int ft_is_empty_list(t_commandList    *head)
{
    if (head == NULL)
        return 1;
    else 
        return 0;
}

int	ft_is_in_list(char	*var, t_env **envlist)
{
	t_env	*tmp;
	
	tmp = *envlist;
	if (tmp == NULL || var == NULL)
		return (0);
	while (tmp != NULL && ft_strcmp(tmp->var, var) != 0)
		tmp = tmp->next;
	return (tmp != NULL);
}

int ft_get_list_size(t_commandList  *head)
{
    int size = 0;
    t_command  *current = head->head;
    while (current != NULL)
    {
        size++;
        current = current->next;
    }
    return size;
}
