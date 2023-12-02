/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_linkedList.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienbelda <julienbelda@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 01:17:07 by bat               #+#    #+#             */
/*   Updated: 2023/12/01 11:31:33 by julienbelda      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command  *ft_getPreviousNode(t_commandList  *head, t_command  *node)
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
    return NULL; // TO CHECK
}

int ft_getListSize(t_commandList  *head)
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

void ft_removeNode(t_commandList **head, t_command *node)
{
    if (*head == NULL || node == NULL)
        return;
    
    if ((*head)->head == node)
        (*head)->head = node->next;

    if (node->next != NULL)
        node->next->prev = node->prev;

    if (node->prev != NULL)
        node->prev->next = node->next;

    // Assurez-vous que les pointeurs prev et next du nœud à supprimer sont à NULL
    node->prev = NULL;
    node->next = NULL;

    free(node);
}

t_command *ft_createNodeCommand(void)
{
    t_command *newNode = malloc(sizeof(t_command));
    
    if (newNode == NULL)
    {
        fprintf(stderr, "Chaos, memory allocation failed with new node\n");
        exit(EXIT_FAILURE);
    }

    // Initialisez les champs de la structure t_command
    newNode->name = NULL;
    newNode->args = NULL;
    newNode->redirectFile = NULL;
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->tokenType = NOT;
    newNode->state = NORMAL;

    return newNode;
}