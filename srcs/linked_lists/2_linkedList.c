/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 01:15:14 by bat               #+#    #+#             */
/*   Updated: 2023/09/28 01:15:16 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Go through list to apply callback function on each element
void ft_iterateList(t_command  *head, void (*callback)(void *data))
{
    t_command  *current = head;
    
    while (current != NULL)
    {
        callback(current->data);
    current = current->next;
    }
}

void ft_freeList(t_command  *head)
{
    t_command  *current = head;
    
    while (current != NULL)
    {
        t_command  *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

void ft_freeNode(t_command  *node)
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

int ft_compareString(void *data, void *target)
{
    char *str = (char *)data;
    char *key = (char *)target;
    return ft_strcmp(str, key);
}

t_command  *ft_findNode(t_command  *head, void *target)
{
    t_command  *current = head;
    while (current != NULL)
    {
        if (ft_compareString(current->data, target) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}
