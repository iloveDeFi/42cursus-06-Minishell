#include "minishell.h"

t_command *ft_process_token(t_commandList *commandList, t_command *currentCommand, char *token) 
{
    t_command *command;
    
    command = currentCommand;
    if (commandList->length == 0) 
        ft_process_first_token_as_command(commandList, token);
    else 
    {
        if (ft_strcmp(command->name, "cd") == 0) 
            ft_process_cd_argument(command, token);
        else 
            ft_process_token_as_argument(commandList, command, token);
    }
    return command;
}

void ft_process_first_token_as_command(t_commandList *commandList, char *token) 
{
    t_command *newCommand;
    
    if (commandList == NULL || token == NULL) 
    {
        perror("Erreur dans ft_process_first_token_as_command : mauvaise entrée à traiter\n");
        return;
    }
    newCommand = ft_create_and_init_new_command_in_commandList(commandList, token);
    commandList->head = newCommand; // head ou tail ?
}

void ft_process_token_as_argument(t_commandList *commandList, t_command *command, char *token) 
{
    char **newArgs;

    if (command == NULL || token == NULL) 
    {
        perror("Erreur dans processTokenAsArgument : mauvaise entrée à traiter\n");
        return;
    }
    newArgs = ft_allocate_and_copy_arguments(commandList, command->args, command->argCount, token);
    free(command->args);
    command->args = newArgs;
    command->argCount++;
}
