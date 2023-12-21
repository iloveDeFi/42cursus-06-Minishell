#include "minishell.h"

void ft_print_command(void *data) 
{
    t_command *command = (t_command *)data;
    if (command != NULL) 
        printf("Command: %s\n", command->name);
}

void print_command(t_command *cmd) 
{
    printf("Command name from print_command : %s\n", cmd->name);

    if (cmd->argCount > 0 && cmd->args != NULL) 
    {
        printf("Arguments:\n");
        for (int i = 0; i < cmd->argCount; i++) 
        {
            printf("%d: %s\n", i + 1, cmd->args[i]);
        }
    }
    else 
    {
        printf("No arguments\n");
    }
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

// adapt casting depending data type to store in list
void ft_printGeneric(void *data)
{
    char *str = (char *)data;
    printf("%s\n", str);
}

void print_command_list(t_commandList *commandList) 
{
    if (commandList == NULL || commandList->head == NULL) {
        printf("Empty command list\n");
        return;
    }

    printf("print_command_list - Command List:\n");
    t_command *current = commandList->head;
    while (current != NULL) {
        printf("print_command_list - Name: %s\n", current->name);
        printf("print_command_list - Token Type: %d\n", current->tokenType);
        printf(" print_command_list - Argument Count: %d\n", current->argCount);
   
        if (current->argCount > 0 && current->args != NULL) {
            printf("print_command_list - Arguments:\n");
            for (int i = 0; i < current->argCount; i++) {
                printf("%d: %s\n", i + 1, current->args[i]);
            }
        } else {
            printf("print_command_list - No arguments\n");
        }
        printf("\n");

        current = current->next;
    }
}