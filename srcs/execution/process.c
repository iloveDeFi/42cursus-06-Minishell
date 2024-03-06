#include "minishell.h"

// void	ft_process_command(t_command *command, char **envp, t_env *envList)
// {
// 	if (!ft_is_builtin(command))
// 		ft_execute_external_command(command, envp);
// 	exit(ft_execute_builtin(command, envList));
// }

t_command *ft_process_token_as_command(t_command *currentCommand, char *token)
{
   if (ft_strcmp(currentCommand->name, "cd") == 0)
        {
            printf("ok\n");
            ft_process_cd_argument(currentCommand, token);
        }
        else
        {
            printf("la\n");
            ft_process_token_as_argument(currentCommand, token);
        }
    return currentCommand;
}

void ft_process_token_as_argument(t_command *command, char *token)
{
    char **newArgs;

    if (command == NULL || token == NULL)
    {
        perror("Erreur dans ft_process_token_as_argument : mauvaise entrée à traiter\n");
        return;
    }

    newArgs = ft_allocate_and_copy_arguments(command, command->args, command->argCount, token);
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
