/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:44:27 by bat               #+#    #+#             */
/*   Updated: 2023/12/12 15:36:25 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// Aficher une commande.

void ft_print_command(void *data) 
{
    t_command *command = (t_command *)data;
    if (command != NULL) 
        printf("Command: %s\n", command->name);
}

// Afiicher la liste de commande.

void ft_print_list(t_commandList *head, void (*printFunction)(void *data)) 
{
    if (head == NULL || head->head == NULL) 
        return;
    t_command *current = head->head;
    while (current != NULL) 
    {
        printFunction(current);
        current = current->next;
    }
}

// Ajouter commande fin de liste.

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

// Fonction pour diviser une chaîne en commandes et les ajouter à la liste

char *ft_custom_strdup(const char *str) {
    size_t len = ft_strlen(str);
    char *copy = malloc(len + 1);

    if (copy == NULL) {
        perror("CHAOS, error allocating memory");
        exit(EXIT_FAILURE);
    }

    ft_strcpy(copy, str);
    return copy;
}

void ft_appendToListArg(t_command *command, const char *arg) 
{
    // Allouer de la mémoire pour la nouvelle chaîne d'argument
    char *argCopy = ft_custom_strdup(arg);
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

int ft_split_arg(t_commandList *commandList, char *input) 
{
    char *token = ft_strtok(input, " ");

    if (token == NULL) {
        fprintf(stderr, "Error: Empty command\n");
        return 0;
    }

    while (token != NULL) 
    {
        t_command *newCommand = ft_createNodeCommand();
        newCommand->name = ft_custom_strdup(token);

        if (newCommand == NULL) 
        {
            perror("CHAOS, error allocating memory");
            ft_destroy_command(commandList);
            exit(EXIT_FAILURE);
        }

        // Avancer le pointeur au prochain argument
        token = ft_strtok(NULL, " ");

        // Ajouter chaque argument à la liste des arguments
        while (token != NULL && *token != '\0' && *token != ' ') 
        {
            ft_appendToListArg(newCommand, token);

            // Avancer le pointeur au prochain argument
            token = ft_strtok(NULL, " ");
        }

        if (commandList->head == NULL) 
        {
            commandList->head = newCommand;
            commandList->tail = commandList->head;
        } 
        else 
        {
            ft_appendToList(commandList, newCommand);
            commandList->tail = commandList->tail->next;
        }

        commandList->length++;
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
                printf("Parsing succeeded. Commands:\n");
                ft_execute_builtin(command, envList);
            } 
            else if (command->name[0] == '.'|| command->name[0] == '/') {
                ft_execute_command_with_path(command->name, commandList, *envList);
            }
            else 
            {
                ft_execute_external_command(command, commandList, *envList);
                printf("Executing external command:\n");
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

t_env *ft_find_envVar(t_envList *envList, const char *targetName) {
    t_env *var = envList->head;

    while (var != NULL) {
        if (ft_strcmp(var->name, targetName) == 0) {
            return var;
        }
        var = var->next;
    }

    return NULL;
}