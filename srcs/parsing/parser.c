/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:44:27 by bat               #+#    #+#             */
/*   Updated: 2023/12/19 20:48:04 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type ft_check_and_allocate_token_type(char *token, int tokenIndex) 
{
    if (tokenIndex == 0 && token[0] != '-') 
    {
        return COMMAND_TYPE;
    }
    else if (token[0] == '-') 
    {
        return OPTION_TYPE;
    }
    else 
    {
        return ARGUMENT_TYPE;
    }
}

int ft_split_arg(t_commandList *commandList, char *input) 
{
    char *token = ft_strtok(input, " ");
    int tokenIndex = 0;

    if (token == NULL) 
    {
        fprintf(stderr, "Error: Empty command\n");
        return 0;
    }
    while (token != NULL) 
    {
        t_command *newCommand = ft_create_node_for_command();
        if (newCommand == NULL) 
        {
            perror("CHAOS, error allocating memory");
            ft_destroy_command(commandList);
            exit(EXIT_FAILURE);
        }
        
        newCommand->name = ft_custom_strdup(token);
        newCommand->tokenType = ft_check_and_allocate_token_type(token, tokenIndex);
        // newCommand->args = 

        switch(newCommand->tokenType) 
        {
            case COMMAND_TYPE:
                printf("Token type: COMMAND\n");
                break;
            case ARGUMENT_TYPE:
                printf("Token type: ARGUMENT\n");
                break;
            case OPTION_TYPE:
                printf("Token type: OPTION\n");
                break;
            default:
                printf("Unknown token type\n");
                break;
        }

        if (commandList->head == NULL) 
        {
            // Première commande dans la liste
            commandList->head = newCommand;
            commandList->tail = commandList->head;
        } 
        else 
        {
            // Ajouter la commande à la fin de la liste
            commandList->tail->next = newCommand;
            commandList->tail = commandList->tail->next;
        }

        commandList->length++;
        token = ft_strtok(NULL, " ");
        tokenIndex++;
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
