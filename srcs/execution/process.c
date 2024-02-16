#include "minishell.h"

t_command *ft_process_token_command_or_argument(t_commandList *commandList, t_command *currentCommand, char *token, char *delimiters) 
{
    if (ft_strcmp(delimiters, " |") == 0)
    {
        if (*token == '|')
            return ft_create_new_command_in_commandList(commandList, NULL);
        else
            ft_process_token_as_argument(commandList, currentCommand, token);
    }
    else
        ft_process_token(commandList, commandList->tail, token);

    return currentCommand;
}

void ft_process_token(t_commandList *commandList, t_command *command, char *token) 
{
    if (commandList->length == 0) 
        ft_process_first_token_as_command(commandList, token);
    else 
    {
        if (ft_strcmp(commandList->tail->name, "cd") == 0) 
        {
            ft_process_cd_argument(commandList->tail, token);
        } 
        else 
        {
            printf("Launch processTokenAsArgument with argument named %s\n", token);
            ft_process_token_as_argument(commandList, commandList->tail, token);
        }
    }
}

void ft_process_token_as_argument(t_commandList *commandList, t_command *command, char *token) 
{
	char **newArgs;

    if (command == NULL || token == NULL) 
    {
        perror("Erreur dans processTokenAsArgument : mauvaise entrée à traiter\n");
        return;
    }
    newArgs = ft_allocate_and_copy_arguments(command->args, command->argCount, token);
    free(command->args);
    command->args = newArgs;
    command->argCount++;
}
