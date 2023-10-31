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
void iterateList(t_node *head, void (*callback)(void *data))
{
    t_node *current = head;
    
    while (current != NULL)
    {
        callback(current->data);
        current = current->next;
    }
}

void freeList(t_node *head)
{
    t_node *current = head;
    
    while (current != NULL)
    {
        t_node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

void freeNode(t_node *node)
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

t_node *findNode(t_node *head, void *target)
{
    t_node *current = head;
    while (current != NULL)
    {
        if (compareString(current->data, target) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}

int compareString(void *data, void *target)
{
    char *str = (char *)data;
    char *key = (char *)target;
    return ft_strcmp(str, key);
}
