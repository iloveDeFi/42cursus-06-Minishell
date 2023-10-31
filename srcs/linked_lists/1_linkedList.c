/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_linkedList.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 01:14:53 by bat               #+#    #+#             */
/*   Updated: 2023/10/31 12:38:46 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void appendToList(t_node **head, void *data) 
{
    t_node *newNode = malloc(sizeof(t_node));
    if (newNode == NULL) 
    {
        fprintf(stderr, "Error when allocating memory\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (*head == NULL) 
        *head = newNode;
    else 
    {
        t_node *currentNode = *head;
        while (currentNode->next != NULL)
            currentNode = currentNode->next;
        currentNode->next = newNode;
        newNode->prev = currentNode;
    }
}

void    *getLastElement(t_node *head)
{
	if (head == NULL)
        return NULL;
    t_node *current = head;
    while (current->next != NULL)
        current = current->next;
    return current->data;
}

int isListEmpty(t_node *head)
{
    if (head == NULL)
        return 1;
    else 
        return 0;
}

void	print_list(t_node *head, void (*printFunction)(void *data))
{
    t_node *current = head;
    while (current != NULL)
    {
        printFunction(current->data);
        current = current->next;
    }
}

// adapt casting depending data type to store in list
void printGeneric(void *data)
{
    char *str = (char *)data;
    printf("%s\n", str);
}
