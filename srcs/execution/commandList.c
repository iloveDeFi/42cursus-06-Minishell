#include "minishell.h"

void ft_initialize_commandList(t_commandList *commandList) 
{
    if (commandList == NULL) 
    {
        fprintf(stderr, "Error: NULL pointer in ft_init_commandList\n");
        exit(EXIT_FAILURE);
    }

    commandList->head = NULL;
    commandList->tail = NULL;
    commandList->length = 0;
    printf("commandlist ok\n");
}

// void ft_execute_command_list(t_commandList *commandList, t_env *envList, char **envp) 
// {
//     // int num_commands;
//     t_command *current_command;
    
//     current_command = commandList->head;

//     while (current_command != NULL) 
//     {
//         if (current_command->tokenType == PIPE) 
//         {
//             // Execute commands with pipes
//             //num_commands = ft_count_number_of_pipes(current_command);
//             ft_execute_piped_commands(current_command, num_commands);
//         } 
//         else 
//         {
//             // Execute single command
//             ft_execute_single_command(current_command, commandList, envList, envp);
//         }

//         current_command = current_command->next;
//     }
// }

void ft_print_commandList(t_commandList *commandList) 
{
    if (commandList == NULL || commandList->head == NULL) 
    {
        fprintf(stderr, "Command list is empty or NULL.\n");
        return;
    }
    
    int i;
    t_command *current;
    
    current = commandList->head;

    printf("Enter ft_print_commandList and command list contains :\n");

    while (current != NULL) 
    {
        printf("Command: %s\n", current->name);

        // Print arguments
        i = 0;
        while (i < current->argCount) 
        {
            printf("Argument %d: %s\n", i, current->args[i]);
            i++;
        }
        current = current->next;
    }
}