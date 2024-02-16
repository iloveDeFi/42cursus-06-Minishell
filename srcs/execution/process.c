#include "minishell.h"

void ft_process_token_or_argument(t_commandList *commandList, t_command *command, char *token, char *delimiters) 
{
    if (ft_strcmp(delimiters, " |") == 0)
    {
        if (*token == '|')
            command = ft_create_new_command_in_commandList(commandList, NULL);
        else
            ft_process_token_as_argument(commandList, command, token);
    }
    else
        ft_process_token(commandList, commandList->tail, token);
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
    if (command == NULL || token == NULL) 
    {
        perror("Erreur dans processTokenAsArgument : mauvaise entrée à traiter\n");
        return;
    }

    char **newArgs = ft_allocate_and_copy_arguments(command->args, command->argCount, token);

    free(command->args);
    command->args = newArgs;
    command->argCount++;
}

// Fonction utilitaire pour allouer de la mémoire et copier les arguments
char **ft_allocate_and_copy_arguments(char **oldArgs, int argCount, char *newArg) 
{
    char **newArgs = (char **)malloc((argCount + 2) * sizeof(char *));
    
    if (newArgs == NULL) 
    {
        perror("CHAOS, erreur d'allocation mémoire dans processTokenAsArgument");
        ft_destroy_command(commandList);
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (i < argCount) 
    {
        newArgs[i] = oldArgs[i];
        i++;
    }

    // Ajout du nouveau token en tant que nouvel argument
    newArgs[argCount] = ft_strdup(newArg);
    if (newArgs[argCount] == NULL)
    {
        perror("Erreur d'allocation mémoire dans processTokenAsArgument");
        ft_destroy_command(commandList);
        exit(EXIT_FAILURE);
    }

    // Ajout d'un pointeur NULL à la fin du tableau
    newArgs[argCount + 1] = NULL;

    return newArgs;
}
