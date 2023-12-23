/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:44:27 by bat               #+#    #+#             */
/*   Updated: 2023/12/23 11:14:54 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_handle_command_type_token(char *token, t_commandList *commandList, int token_index)
{
    t_command *newCommand = ft_create_node_for_command();
    if (newCommand == NULL) 
    {
        perror("CHAOS, error allocating memory, newCommand is NULL");
        // ft_destroy_single_command(newCommand);
        // return error value not exit ?
        exit(EXIT_FAILURE);
    }
    newCommand->name = ft_custom_strdup(token);
    newCommand->tokenType = ft_define_token_type(token, token_index);
    ft_appendToList(commandList, newCommand);
}

void ft_handle_argument_type_token(char *token,t_command *command)
{
 
        ft_append_argument_to_command_node(command, token);
        // ft_print_string_array(command->args);
}

char **ft_send_token_in_good_list(char *token, int token_index, t_token_type token_type, t_commandList *commandList) 
{
    t_command *newCommand;

    newCommand = NULL;
    
    if (token_type == COMMAND_TYPE)
    {
        ft_handle_command_type_token(token, commandList, token_index);
    }
    else if (token_type == ARGUMENT_TYPE) 
    {
        ft_handle_argument_type_token(token, newCommand);
    }
    // ft_print_string_array(command->args);
    return newCommand->args;
}

t_token_type ft_define_token_type(char *token, int tokenIndex) 
{
    if (tokenIndex == 0 && token[0] != '-') {
        return COMMAND_TYPE;
    } else if (token[0] == '-') {
        return OPTION_TYPE;
    } else if (strcmp(token, "|") == 0) {
        return PIPE;
    } else if (strcmp(token, "<<") == 0) {
        return HEREDOC;
    } else if (strcmp(token, "(") == 0) {
        return LPR;
    } else if (strcmp(token, ")") == 0) {
        return RPR;
    } else if (strcmp(token, "&&") == 0) {
        return AND;
    } else if (strcmp(token, "||") == 0) {
        return OR;
    } else if (strcmp(token, ">>") == 0) {
        return APPEND;
    } else if (strcmp(token, ">") == 0) {
        return OUT;
    } else if (strcmp(token, "<") == 0) {
        return IN;
    } else {
        return ARGUMENT_TYPE;
    }
}

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
        //newCommand->args = ft_edit_args_argument_value(newCommand->args, token, newCommand->argCount);
        // print_command(newCommand);
        // print_command_list(commandList);
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
