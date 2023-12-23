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
    if (command == NULL) 
    {
        perror("Error: Command node is NULL");
        return;
    }
    ft_append_argument_to_command_node(command, token);
    // ft_print_string_array(command->args);
}

char **ft_send_token_in_good_list(char *token, int token_index, t_token_type token_type, t_commandList *commandList) 
{
    //t_command *newCommand;
    t_command *lastCommand;

    //newCommand = NULL;
    
    if (token_type == COMMAND_TYPE)
    {
        ft_handle_command_type_token(token, commandList, token_index);
    }
    else if (token_type == ARGUMENT_TYPE) 
    {
        lastCommand = commandList->tail;
        if (lastCommand == NULL) 
        {
            perror("Error: No command node in the list");
            return NULL;
        }
        ft_handle_argument_type_token(token, lastCommand);
        ft_print_string_array(lastCommand->args);
    }
    // ft_print_string_array(command->args);
    return commandList->tail->args;
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
