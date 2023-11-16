/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_linkedList.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 01:17:07 by bat               #+#    #+#             */
/*   Updated: 2023/11/15 15:47:02 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node *getPreviousNode(t_node *head, t_node *node)
{
    t_node *current = head;
    t_node *previous = NULL;
    while (current != NULL)
    {
        if(current == node)
            return previous;
        previous = current;
        current = current->next;
    }
    return NULL; // TO CHECK
}

int getListSize(t_node *head)
{
    int size = 0;
    t_node *current = head;
    while (current != NULL)
    {
        size++;
        current = current->next;
    }
    return size;
}

void removeNode(t_node **head, t_node *node)
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

t_node *ft_createNode(void *data)
{
    t_node *newNode = malloc(sizeof(t_node));
    
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