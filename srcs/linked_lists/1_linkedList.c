#include "minishell.h"

void ft_appendToList(t_command  **head, void *data) 
{
    t_command  *newNode = malloc(sizeof(t_command ));
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
        t_command  *currentNode = *head;
        while (currentNode->next != NULL)
            currentNode = currentNode->next;
        currentNode->next = newNode;
        newNode->prev = currentNode;
    }
}

void    *getLastElement(t_command  *head)
{
	if (head == NULL)
        return NULL;
    t_command  *current = head;
    while (current->next != NULL)
        current = current->next;
    return current->data;
}

int ft_isListEmpty(t_command  *head)
{
    if (head == NULL)
        return 1;
    else 
        return 0;
}

void    ft_print_list(t_command  *head, void (*printFunction)(void *data))
{
    t_command  *current = head;
    while (current != NULL)
    {
        printFunction(current->data);
        current = current->next;
    }
}

// adapt casting depending data type to store in list
void ft_printGeneric(void *data)
{
    char *str = (char *)data;
    printf("%s\n", str);
}
