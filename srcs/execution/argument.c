#include "minishell.h"

char **ft_allocate_memory_for_arguments(t_command *command, int argCount)
{
    char **newArgs = (char **)malloc((argCount + 2) * sizeof(char *));
    if (newArgs == NULL)
    {
        perror("CHAOS, erreur d'allocation mémoire dans processTokenAsArgument");
        // ft_destroy_commandList(command);
        exit(EXIT_FAILURE);
    }
    return newArgs;
}

void ft_copy_existing_arguments(char **newArgs, char **oldArgs, int argCount)
{
    int i = 0;
    while (i < argCount)
    {
        newArgs[i] = oldArgs[i];
        i++;
    }
}

void ft_copy_new_argument(t_command *command, char **newArgs, int argCount, char *newArg)
{
    newArgs[argCount] = ft_strdup(newArg);
    if (newArgs[argCount] == NULL)
    {
        perror("Erreur d'allocation mémoire dans processTokenAsArgument");
        // ft_destroy_commandList(command);
        exit(EXIT_FAILURE);
    }
}

void ft_add_null_terminator(char **newArgs, int argCount)
{
    newArgs[argCount + 1] = NULL;
}

char **ft_allocate_and_copy_arguments(t_command *command, char **oldArgs, int argCount, char *newArg)
{
    char **newArgs = ft_allocate_memory_for_arguments(command, argCount);
    ft_copy_existing_arguments(newArgs, oldArgs, argCount);
    ft_copy_new_argument(command, newArgs, argCount, newArg);
    ft_add_null_terminator(newArgs, argCount);
    return newArgs;
}
