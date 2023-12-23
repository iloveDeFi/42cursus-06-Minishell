/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:44:27 by bat               #+#    #+#             */
/*   Updated: 2023/12/23 12:01:37 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_split_arg(t_commandList *commandList, char *input) 
{
    char *token;
    int token_index;

    token = ft_strtok(input, " ");
    token_index = 0;
    if (token == NULL) 
    {
        fprintf(stderr, "Error: Empty command\n");
        return 0;
    }
    while (token != NULL) 
    {
        t_token_type token_type = ft_define_token_type(token, token_index);
        ft_send_token_in_good_list(token, token_index, token_type, commandList);
        // ft_print_command(newCommand);
        ft_print_command_list(commandList);
        token_index++;
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
            // ft_print_list(commandList, ft_print_command);
            t_command *command = commandList->head;
            if (ft_is_builtin(command)) 
            {
                printf("Builtin detected. Calling ft_execute_builtin.\n");
                ft_execute_builtin(command, envList);
            } 
            else if (command->name[0] == '.'|| command->name[0] == '/') 
            {
                printf("Relative or absolute path detected. Calling ft_execute_command_with_path.\n");
                ft_execute_command_with_path(command);
            }
            else 
            {
                printf("Calling ft_execute_external_command.\n");
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
        perror("Parsing failed in ft_split_arg");
        ft_destroy_command(commandList);
        return 0;
    }
}
