#include "minishell.h"

void ft_add_to_list(t_env **envlist, t_env *new_node)
{
    if (!envlist || !new_node)
        return;

    new_node->next = *envlist;
    *envlist = new_node;
}

int	ft_add_envVar_to_list(t_env **envlist, char *args)
{
	t_env	*new_node;

	new_node = ft_create_node(args);
	if (!new_node)
		return (0);
	if (!ft_is_in_lst(new_node->var, envlist))
		ft_add_to_list(envlist, new_node);
	else
		ft_replace_in_list(new_node, envlist);
	return (1);
}

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

void ft_append_argument_to_command_node(t_command *command, const char *token) 
{
    if (command->args == NULL) 
    {
        command->args = malloc(100 * sizeof(char *));
        // command->args = (char **)malloc(2 * sizeof(char *));
        if (command->args == NULL) 
        {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        command->args[0] = ft_custom_strdup(token);
        command->args[1] = NULL; 
        command->argCount = 1;
    } 
    else 
    {
        // Réallouer de la mémoire pour contenir un nouvel argument
        command->args = (char **)realloc(command->args, (command->argCount + 2) * sizeof(char *));
        if (command->args == NULL) 
        {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        command->args[command->argCount] = ft_custom_strdup(token);
        command->args[command->argCount + 1] = NULL;
        command->argCount++;
    }
}
