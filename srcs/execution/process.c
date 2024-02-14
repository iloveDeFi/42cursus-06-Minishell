#include "minishell.h"

int	ft_process_input_with_strtok(t_commandList *commandList, char *input, char *delimiters) 
{
    char *token;
    char inputCopy[ft_strlen(input) + 1];
    int tokenIndex;

    tokenIndex = 0;
    ft_strcpy(inputCopy, input);

    token = ft_strtok(inputCopy, delimiters);
    while (token != NULL) 
    {
        ft_process_token(commandList, commandList->tail, token);
        tokenIndex++;
        token = ft_strtok(NULL, delimiters);
    }

    return commandList->length;
}

// Fonction pour traiter un seul token
void	ft_process_token(t_commandList *commandList, t_command *command, char *token) 
{
    if (command == NULL || token == NULL) 
    {
        perror("Erreur dans processToken : mauvaise entrée à traiter\n");
        return;
    }

    if (commandList->length == 0) 
    {
        // Premier token de la liste
        ft_process_first_token_as_command(commandList, token);
    } 
    else 
    {
        // Les tokens suivants sont des arguments
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

// Fonction pour traiter le premier token comme une commande
void	ft_process_first_token_as_command(t_commandList *commandList, char *token) 
{
    t_command *command = NULL;

    if (!ft_check_if_pipe_in_string(token)) 
    {
        command = (t_command *)malloc(sizeof(t_command));

        if (command == NULL) 
        {
            perror("CHAOS, error allocating memory");
            ft_destroy_command(commandList);
            exit(EXIT_FAILURE);
        }

        ft_init_new_node(commandList, command, token);
        ft_append_to_commandList(commandList, command);

        printf("Printing commandList at the end of processFirstTokenAsCommand:\n");
        ft_print_commandList(commandList);
    }
}

// Fonction pour traiter un token comme un argument
void	ft_process_token_as_argument(t_commandList *commandList, t_command *command, char *token) 
{
    if (command == NULL || token == NULL) 
    {
        perror("Erreur dans processTokenAsArgument : mauvaise entrée à traiter\n");
        return;
    }

    char **newArgs = (char **)malloc((command->argCount + 2) * sizeof(char *));
    if (newArgs == NULL) 
    {
        perror("CHAOS, erreur d'allocation mémoire dans processTokenAsArgument");
        ft_destroy_command(commandList);
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (i < command->argCount) 
    {
        newArgs[i] = command->args[i];
        i++;
    }

    // Ajout du nouveau token en tant que nouvel argument
    newArgs[command->argCount] = ft_strdup(token);
    if (newArgs[command->argCount] == NULL)
    {
        perror("Erreur d'allocation mémoire dans processTokenAsArgument");
        ft_destroy_command(commandList);
        exit(EXIT_FAILURE);
    }

    // Ajout d'un pointeur NULL à la fin du tableau
    newArgs[command->argCount + 1] = NULL;

    // Libération de la mémoire de l'ancien tableau d'arguments
    free(command->args);

    // Mise à jour du pointeur vers le nouveau tableau d'arguments
    command->args = newArgs;
    command->argCount++;
}