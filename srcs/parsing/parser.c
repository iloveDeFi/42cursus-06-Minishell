/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienbelda <julienbelda@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:44:27 by bat               #+#    #+#             */
/*   Updated: 2023/12/02 20:32:27 by julienbelda      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Initialiser la liste de commande

void ft_init_commandList(t_commandList *commandList) 
{
    if (commandList == NULL) {
        fprintf(stderr, "Error: NULL pointer in ft_init_commandList\n");
        exit(EXIT_FAILURE);
    }

    commandList->head = NULL;
    commandList->tail = NULL;
    commandList->length = 0;
}

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


// Détruire liste de commandes.

void destroy_commands(t_commandList *commandList) 
{
    t_command *current = commandList->head;
    while (current != NULL) 
    {
        t_command *next = current->next;
        free(current->name);
        free(current);
        current = next;
    }
    commandList->head = NULL;
    commandList->tail = NULL;
    commandList->length = 0;
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

int ft_split_arg(t_commandList *commandList, char *input) 
{
    char *token = ft_strtok(input, " ");

    while (token != NULL) 
    {
        t_command *newCommand = ft_createNodeCommand();

        newCommand->name = ft_strdup(token);

        if (newCommand == NULL) 
        {
            perror("CHAOS, error allocating memory");
            destroy_commands(commandList);
            exit(EXIT_FAILURE);
        }
        if (newCommand->name == NULL) 
        {
            perror("CHAOS, error allocating memory");
            free(newCommand);
            destroy_commands(commandList);
            exit(EXIT_FAILURE);
        }
        if (commandList->head == NULL) 
        {
            commandList->head = newCommand;
            commandList->tail = commandList->head;
        } else 
        {
            ft_appendToList(commandList, newCommand);
            commandList->tail = commandList->tail->next;
        }
        commandList->length++;
        token = ft_strtok(NULL, " ");
    }
    return commandList->length;
}

int ft_test_parsing(t_commandList *commandList, char *input ,t_env **envList)
{
    ft_init_commandList(commandList);
    if (ft_split_arg(commandList, input) > 0) 
    {
        if (commandList != NULL && commandList->head != NULL) 
        {
            ft_print_list(commandList, ft_print_command);
            t_command *cmd = commandList->head;
            if (ft_is_builtins(cmd)) 
            {
                printf("Parsing succeeded. Commands:\n");
                ft_exec_builtins(cmd, envList);
            } 
            else 
            {
                // Ici, vous pouvez implémenter la logique pour exécuter des commandes externes
                // ou gérer d'autres cas selon les besoins de votre programme.
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
        destroy_commands(commandList);  // Libération mémoire en cas d'échec
        return 0;
    }
}

// // Fonction pour tester la division de la chaîne en commandes
// int ft_test_parsing(t_commandList *commandList, char *input) {
//     // ft_init_commandList(commandList);
    

//     if (ft_split_arg(commandList, input) > 0) {
//         printf("Parsing succeeded. Commands:\n");
//         if (commandList != NULL)
//             ft_print_list(commandList, ft_print_command);
//         else
//             fprintf(stderr, "Error: commandList is NULL\n");
//         return 1;
//     } else {
//         perror("Parsing failed");
//         destroy_commands(commandList);  // Libération mémoire en cas d'échec
//         return 0;
//     }
// }

// int ft_split_arg(t_commandList *commandList, char *input)
// {
//     char *token;
    
//     token = ft_strtok(input, " ");
//     while (token != NULL)
//     {
//         t_command *newCommand = malloc(sizeof(t_command));
//         if (newCommand == NULL)
//         {
//             perror("CHAOS, error allocating memory");
//             exit(EXIT_FAILURE);
//         }
//         newCommand->name = ft_strdup(token);

//         if (commandList->head == NULL)
//         {
//             commandList->head = ft_createNodeCommand(newCommand);
//             commandList->tail = commandList->head;
//         }
//         else 
//         {
//             ft_appendToList(commandList, newCommand);
//             commandList->tail = commandList->tail->next;
//         }

//         commandList->length++;
//         token = ft_strtok(NULL, " ");
//     }

//     return commandList->length;
// }


t_env *ft_find_envVar(t_envList *envList, const char *targetName) {
    t_env *var = envList->head;  // Début de la liste

    while (var != NULL) {
        if (strcmp(var->var, targetName) == 0) {  // Comparaison avec le nom de la variable
            return var;
        }
        var = var->next;
    }

    return NULL;  // Aucune correspondance trouvée
}