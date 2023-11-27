/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:44:27 by bat               #+#    #+#             */
/*   Updated: 2023/11/27 18:11:30 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_init_commandList(t_commandList *commandList)
{
    if (commandList == NULL)
    {
        // Gérer l'erreur si le pointeur est NULL
        return;
    }

    // Initialisez les membres de la structure t_commandList
    commandList->head = NULL;
    commandList->tail = NULL;
    commandList->length = 0;
}

int ft_test_parsing(t_commandList *commandList, char *input)
{
    ft_init_commandList(commandList);
    if (ft_split_arg(commandList, input))
        return (0);
    else {
        perror("parsing failed");
        return (1);
    }
}

int ft_split_arg(t_commandList *commandList, char *input)
{
    char *token;
    
    token = ft_strtok(input, " ");
    while (token != NULL)
    {
        t_command *newCommand = malloc(sizeof(t_command));
        if (newCommand == NULL)
        {
            perror("CHAOS, error allocating memory");
            exit(EXIT_FAILURE);
        }
        newCommand->name = ft_strdup(token);

        if (commandList->head == NULL)
        {
            commandList->head = ft_createNodeCommand(newCommand);
            commandList->tail = commandList->head;
        }
        else 
        {
            ft_appendToList(&(commandList->head), ft_createNodeCommand(newCommand));
            commandList->tail = commandList->tail->next;
        }

        commandList->length++;
        token = ft_strtok(NULL, " ");
    }

    return commandList->length;
}

t_envVar *ft_find_envVar(t_envVar *head, const char *targetName)
{
    t_envVar *current = head;
    while (current != NULL)
    {
        if (ft_strcmp(current->name, targetName) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}
