/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:44:27 by bat               #+#    #+#             */
/*   Updated: 2023/12/22 20:55:57 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*char **ft_edit_args_argument_value(char **array, const char *value, int index) 
{
    int count = ft_count_number_of_elements_in_array(array);

    // Si l'index est plus grand que le nombre actuel d'éléments, réalloue le tableau
    if (index >= count) {
        char **temp = realloc(array, (index + 2) * sizeof(char *));
        if (temp == NULL) {
            return NULL;
        }
        array = temp;
        for (int i = count; i <= index; i++) {
            array[i] = NULL;
        }
    }
    // Ajoute ou modifie la valeur à l'index spécifié
    if (array[index] == NULL) {
        array[index] = ft_custom_strdup(value);
    } else {
        free(array[index]);
        array[index] = ft_custom_strdup(value);
    }
    return array;
}
*/

char **ft_send_token_in_good_list(char *token, t_command *command) 
{
    if (command->tokenType == COMMAND_TYPE) 
    {
        command->name = ft_custom_strdup(token);
    } 
    else if (command->tokenType == ARGUMENT_TYPE) 
    {
        /*
        if (command->argCount == 0) 
        {
            command->args = malloc(2 * sizeof(char *));
        }
        else 
        {
            command->args = ft_realloc(command->args, (command->argCount + 2) * sizeof(char *));
        }
        */
        ft_append_argument_to_command_node(command, token);
        command->args[command->argCount] = ft_custom_strdup(token);
        // ft_print_string_array(command->args);
        command->args[command->argCount + 1] = NULL;
        command->argCount++;
    }
    // ft_print_string_array(command->args);
    return command->args;
}

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
        
        newCommand->tokenType = ft_check_and_allocate_token_type(token, tokenIndex);
        ft_send_token_in_good_list(token, newCommand);
        // TO DO FREE newCommand->args when not used anymore
        newCommand->name = ft_custom_strdup(token);
        //newCommand->args = ft_edit_args_argument_value(newCommand->args, token, newCommand->argCount);
        if (commandList->head == NULL) 
        {
            commandList->head = newCommand;
            commandList->tail = commandList->head;
        } 
        else 
        {
            commandList->tail->next = newCommand;
            commandList->tail = commandList->tail->next;
        }

        commandList->length++;
        token = ft_strtok(NULL, " ");
        tokenIndex++;
        // print_command(newCommand);
        //print_command_list(commandList);
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
