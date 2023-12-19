#include "minishell.h"

void ft_appendToList(t_commandList *commandList, t_command *newCommand) 
{
    if (commandList->tail == NULL) 
    {
        fprintf(stderr, "Error: Attempting to append to an empty list\n");
        exit(EXIT_FAILURE);
    }

    commandList->tail->next = newCommand;
    newCommand->next = NULL;
}

void ft_appendToListArg(t_command *command) 
{
    // Allouer de la mémoire pour la nouvelle chaîne d'argument
    char *argCopy = ft_custom_strdup(*command->args);
    if (argCopy == NULL) 
    {
        perror("CHAOS, error allocating memory");
        exit(EXIT_FAILURE);
    }

    // Allouer de la mémoire pour la liste d'arguments
    command->args = malloc(sizeof(char *));
    if (command->args == NULL) 
    {
        perror("CHAOS, error allocating memory");
        exit(EXIT_FAILURE);
    }

    // Ajouter le nouvel argument à la liste
    command->args[0] = argCopy;
    command->argCount = 1;
}

void ft_print_list(t_commandList *head, void (*printFunction)(void *data)) 
{
    if (head == NULL || head->head == NULL) 
        return;
    t_command *current = head->head;
    while (current != NULL) 
    {
        printFunction(current);
        current = current->next;
    }
}

void ft_print_command(void *data) 
{
    t_command *command = (t_command *)data;
    if (command != NULL) 
        printf("Command: %s\n", command->name);
}

void ft_append_to_argument_list(t_command *command, const char *arg) {
    // Vérifier si args est vide ou non initialisé
    if (command->args == NULL) {
        command->args = (char **)malloc(sizeof(char *));
        if (command->args == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        command->args[0] = ft_custom_strdup(arg);
        command->argCount = 1;
    } else {
        // Réallouer de la mémoire pour contenir un nouvel argument
        command->args = (char **)realloc(command->args, (command->argCount + 1) * sizeof(char *));
        if (command->args == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        command->args[command->argCount] = ft_custom_strdup(arg);
        command->argCount++;
    }
}
