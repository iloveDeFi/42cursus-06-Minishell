/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienbelda <julienbelda@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:44:27 by bat               #+#    #+#             */
/*   Updated: 2023/12/19 11:17:21 by julienbelda      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_split_arg(t_commandList *commandList, char *input) 
{
    char *token = ft_strtok(input, " ");

    if (token == NULL) 
    {
        fprintf(stderr, "Error: Empty command\n");
        return 0;
    }

    while (token != NULL) 
    {
        t_command *newCommand = ft_create_node_for_command();
        newCommand->name = ft_custom_strdup(token);

        if (newCommand == NULL) 
        {
            perror("CHAOS, error allocating memory");
            ft_destroy_command(commandList);
            exit(EXIT_FAILURE);
        }

        if (commandList->head == NULL) 
        {
            // Première commande dans la liste
            commandList->head = newCommand;
            commandList->tail = commandList->head;
        } 
        else 
        {
            // Ajoutez la commande à la fin de la liste
            commandList->tail->next = newCommand;
            commandList->tail = commandList->tail->next;
        }

        commandList->length++;
        token = ft_strtok(NULL, " ");
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
