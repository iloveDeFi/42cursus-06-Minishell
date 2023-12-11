/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:44:27 by bat               #+#    #+#             */
/*   Updated: 2023/12/11 16:29:49 by bat              ###   ########.fr       */
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



int ft_test_parsing(t_commandList *commandList, char *input ,t_env **envList)
{
    ft_initialize_commandList(commandList);
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
                ft_execute_external_command(cmd->name, cmd->args, *envList);
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