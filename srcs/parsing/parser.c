/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:44:27 by bat               #+#    #+#             */
/*   Updated: 2023/11/27 13:35:37 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int ft_split_arg(t_argList *argList, char *input)
{
    char *token;
    
    token = ft_strtok(input, " ");
    while (token != NULL)
    {
        t_arg *newArg = malloc(sizeof(t_arg));
        if (newArg == NULL)
        {
            perror("CHAOS, error allocating memory");
            exit(EXIT_FAILURE);
        }
        newArg->name = ft_strdup(token);
        if (argList->head == NULL)
        {
            argList->head = newArg;
            argList->tail = newArg;
            newArg->prev = NULL; 
        }
        else {
            newArg->prev = argList->tail;
            //argList->tail->next = newArg;
            argList->tail = newArg;
        }
        argList->arglistLength++;
        token = strtok(NULL, " ");
    }
    return argList->arglistLength;
}*/

int test_parsing(t_list *commandList, char *input)
{
    if (ft_split_arg(commandList, input))
        return (0);
    else {
        perror("parsing failed");
        return (1);
    }
}

int ft_split_arg(t_list *commandList, char *input)
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
            commandList->head = ft_createNode(newCommand);
            commandList->tail = commandList->head;
        }
        else 
        {
            appendToList(&(commandList->head), ft_createNode(newCommand));
            commandList->tail = commandList->tail->next;
        }

        commandList->length++;
        token = strtok(NULL, " ");
    }

    return commandList->length;
}

/*char *ft_find_envVar(t_envVar *head, const char *targetName)
{
    t_envVar *current = head;
    while (current != NULL)
    {
        if (ft_strcmp(current->name, targetName) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}*/

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
