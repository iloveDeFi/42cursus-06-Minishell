/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_linkedList.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 01:17:07 by bat               #+#    #+#             */
/*   Updated: 2023/11/27 15:27:50 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command  *ft_getPreviousNode(t_command  *head, t_command  *node)
{
    t_command *current = head;
    t_command  *previous = NULL;
    while (current != NULL)
    {
        if(current == node)
            return previous;
        previous = current;
        current = current->next;
    }
    return NULL; // TO CHECK
}

int ft_getListSize(t_command  *head)
{
    int size = 0;
    t_command  *current = head;
    while (current != NULL)
    {
        size++;
        current = current->next;
    }
    return size;
}

void ft_removeNode(t_command **head, t_command *node)
{
    if (*head == NULL || node == NULL)
        return;
    if (*head == node)
        *head = node->next;
    if (node->next != NULL)
        node->next->prev = node->prev;
    if (node->prev != NULL)
        node->prev->next = node->next;
    free(node);
}

t_command *ft_createNodeCommand(void *data)
{
    t_command *newNode = malloc(sizeof(t_command));
    
    if (newNode == NULL)
    {
        fprintf(stderr, "Chaos, memory allocation failed with new node\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    
    return newNode;
}