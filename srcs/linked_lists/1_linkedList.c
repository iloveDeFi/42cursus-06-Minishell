#include "minishell.h"

// void ft_appendToList(t_commandList *list, t_command *newCommand) 
// {
//     if (list == NULL || newCommand == NULL) {
//         return;
//     }

//     if (list->head == NULL) {
//         // Si la liste est vide, le nouvel élément devient la tête de la liste
//         list->head = newCommand;
//         list->tail = newCommand;
//         newCommand->next = NULL;
//     } else {
//         // Sinon, ajoutez le nouvel élément à la fin de la liste
//         list->tail->next = newCommand;
//         list->tail = newCommand;
//         newCommand->next = NULL;
//     }

//     list->length++;
// }


void    *getLastElement(t_commandList *head)
{
	if (head == NULL)
        return NULL;
    t_command *current = head->head;
    while (current->next != NULL)
        current = current->next;
    return current->data;
}

int ft_isListEmpty(t_commandList    *head)
{
    if (head == NULL)
        return 1;
    else 
        return 0;
}


// adapt casting depending data type to store in list
void ft_printGeneric(void *data)
{
    char *str = (char *)data;
    printf("%s\n", str);
}
