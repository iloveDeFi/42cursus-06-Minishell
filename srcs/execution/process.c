#include "minishell.h"

t_command *ft_process_token(t_commandList *commandList, t_command *currentCommand, char *token) 
{
    //printf("enter processtoken\n");
    if (commandList->length == 0) 
    {    
        printf("hey\n");
        return ft_process_first_token_as_command(commandList, token);
    }
    
    else 
    {
        if (ft_strcmp(currentCommand->name, "cd") == 0) 
        {    
            printf("ok\n");
            ft_process_cd_argument(currentCommand, token);
        }
        else
        {   
            printf("la\n");
            ft_process_token_as_argument(commandList, currentCommand, token);
        }
    }
    return currentCommand;
}

t_command *ft_process_first_token_as_command(t_commandList *commandList, char *token) 
{
    printf("enter process as command\n");
    if (commandList == NULL || token == NULL) 
    {
        perror("Erreur dans ft_process_first_token_as_command : mauvaise entrée à traiter\n");
        return NULL;
    }
    return ft_create_and_init_new_command_in_commandList(commandList, token);
}

void ft_process_token_as_argument(t_commandList *commandList, t_command *command, char *token) 
{
    char **newArgs;

    if (command == NULL || token == NULL) 
    {
        perror("Erreur dans ft_process_token_as_argument : mauvaise entrée à traiter\n");
        return;
    }

    newArgs = ft_allocate_and_copy_arguments(commandList, command->args, command->argCount, token);
    if (newArgs == NULL) 
    {
        free(command->name);
        free(command->args);
        perror("Erreur dans ft_allocate_and_copy_arguments : mauvaise entrée à traiter\n");
        return;
    }

    free(command->args);
    command->args = newArgs;
    command->argCount++;
}
