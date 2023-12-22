/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienbelda <julienbelda@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:44:27 by bat               #+#    #+#             */
/*   Updated: 2023/12/22 15:21:41 by julienbelda      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type ft_check_and_allocate_token_type(char *token, int tokenIndex) 
{
    if (tokenIndex == 0 && token[0] != '-') 
    {
        return COMMAND_TYPE;
    }
    else 
    {
        return ARGUMENT_TYPE;
    }
}

void process_command(t_commandList *commandList, char *token) 
{
    t_command *command = ft_create_node_for_command();
    if (command == NULL) 
    {
        perror("CHAOS, error allocating memory");
        ft_destroy_command(commandList);
        exit(EXIT_FAILURE);
    }

    command->name = ft_strdup(token);
    command->tokenType = COMMAND_TYPE;

    // Aucune allocation initiale pour le tableau d'arguments
    command->args = NULL;

    if (commandList->head == NULL) 
    {
        // Première commande dans la liste
        commandList->head = command;
        commandList->tail = commandList->head;
    } 
    else 
    {
        // Ajouter la commande à la fin de la liste
        commandList->tail->next = command;
        commandList->tail = commandList->tail->next;
    }

    commandList->length++;
}

// Fonction pour traiter un argument
void process_argument(t_commandList *commandList, t_command *command, char *token, int argIndex) 
{
    if (command == NULL) 
    {
        fprintf(stderr, "An error occurred: not enough arguments\n");
        return;
    }
    t_command *newArg = ft_create_node_for_command();
    if (newArg == NULL) {
        perror("CHAOS, error allocating memory");
        ft_destroy_command(commandList);
        exit(EXIT_FAILURE);
    }
    newArg->name = ft_strdup(token);
    newArg->tokenType = ARGUMENT_TYPE;

    commandList->tail->next = newArg;
    commandList->tail = commandList->tail->next;

    commandList->length++;

    store_argument_in_command(command, newArg->name, argIndex);
}

void store_argument_in_command(t_command *command, char *newArg, int argIndex) 
{
    if (command == NULL || newArg == NULL) 
    {
        fprintf(stderr, "An error occurred: invalid command or argument\n");
        exit(EXIT_FAILURE);
    }
    char **newArgs = malloc(sizeof(char *) * (argIndex + 2));
    if (newArgs == NULL) 
    {
        perror("CHAOS, error allocating memory");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (i < argIndex) 
    {
        if (i < command->argCount && command->args[i] != NULL) 
        {
            newArgs[i] = command->args[i];
        } 
        else 
        {
            fprintf(stderr, "An error occurred: invalid argument in the command\n");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    newArgs[argIndex] = newArg;
    newArgs[argIndex + 1] = NULL;
    free(command->args);
    command->args = newArgs;
}

int ft_split_arg(t_commandList *commandList, char *input) 
{
    char *token = ft_strtok(input, " ");

    if (token == NULL) 
    {
        fprintf(stderr, "An error occurred: Empty command\n");
        return 0;
    }
    // Traitement du premier token comme une commande
    process_command(commandList, token);
    int argIndex = 0;

    while ((token = ft_strtok(NULL, " ")) != NULL) {
        {
            process_argument(commandList, commandList->tail, token, argIndex);
            argIndex++;
        }
    }

    return commandList->length;
}

int ft_launch_parsing(t_commandList *commandList, char *input ,t_env **envList)
{
    ft_initialize_commandList(commandList);
    if (ft_split_arg(commandList, input) > 0) 
    {
        if (commandList != NULL && commandList->head != NULL) 
        {
            ft_print_list(commandList, ft_print_command);
            t_command *command = commandList->head;
            if (ft_is_builtin(command)) 
            {
                printf("Builting. Parsing succeeded. Commands:\n");
                ft_execute_builtin(command, envList);
            } 
            else if (command->name[0] == '.'|| command->name[0] == '/') 
            {
                printf("Relative or absolute path detected.\n");
                ft_execute_command_with_path(command);
            }
            else 
            {
                printf("Call ft_execute_external_command:\n");
                ft_execute_external_command(command, commandList);
            }
        } 
        else 
        {
            fprintf(stderr, "Error: commandList or its head is NULL\n");
        }
        return 1;
    } 
    else 
    {
        perror("Parsing failed");
        ft_destroy_command(commandList);
        return 0;
    }
}


/* int ft_split_arg(t_commandList *commandList, char *input) 
{
    char *token = ft_strtok(input, " ");

    if (token == NULL) {
        fprintf(stderr, "Error: Empty command\n");
        return 0;
    }

    // Traitement du premier token comme une commande
    t_command *command = ft_create_node_for_command();
    if (command == NULL) {
        perror("CHAOS, error allocating memory");
        ft_destroy_command(commandList);
        exit(EXIT_FAILURE);
    }

    command->name = ft_custom_strdup(token);
    command->tokenType = COMMAND_TYPE;

    if (commandList->head == NULL) {
        // Première commande dans la liste
        commandList->head = command;
        commandList->tail = commandList->head;
    } else {
        // Ajouter la commande à la fin de la liste
        commandList->tail->next = command;
        commandList->tail = commandList->tail->next;
    }

    commandList->length++;

    // Traitement des tokens suivants comme des arguments
    int argIndex = 0;
    while ((token = ft_strtok(NULL, " ")) != NULL) {
        t_command *newArg = ft_create_node_for_command();
        if (newArg == NULL) {
            perror("CHAOS, error allocating memory");
            ft_destroy_command(commandList);
            exit(EXIT_FAILURE);
        }

        newArg->name = ft_custom_strdup(token);
        newArg->tokenType = ARGUMENT_TYPE;

        // Ajouter l'argument à la fin de la liste
        commandList->tail->next = newArg;
        commandList->tail = commandList->tail->next;

        commandList->length++;

        // Stocker l'argument dans le champ args de la commande
        if (argIndex == 0) {
            command->args = malloc(sizeof(char *) * 2); // +1 pour le dernier NULL
        } else {
            command->args = realloc(command->args, sizeof(char *) * (argIndex + 2));
        }

        if (command->args == NULL) {
            perror("CHAOS, error allocating memory");
            ft_destroy_command(commandList);
            exit(EXIT_FAILURE);
        }

        command->args[argIndex] = newArg->name;
        command->args[argIndex + 1] = NULL;

        argIndex++;
    }

    return commandList->length;
} */