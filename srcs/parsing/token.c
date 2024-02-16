#include "minishell.h"

char *ft_change_strtok_delimiter(t_commandList *commandList, char *input) 
{
    char *delimiters = " ";

    if (ft_check_if_pipe_in_string(input))
    {
        delimiters = " |";
    }

    return delimiters;
}

int ft_tokenize_input_with_strtok(t_commandList *commandList, char *input, char *delimiters) 
{
    char *token;
    char inputCopy[ft_strlen(input) + 1];
    int tokenIndex;
    char *ptr;
    t_command *command;

    tokenIndex = 0;
    ft_strcpy(inputCopy, input);
    ptr = inputCopy;
    command = NULL;

    token = ft_strtok(inputCopy, delimiters);
    while (token != NULL) 
    {
        ft_process_token_or_argument(commandList, command, token, delimiters);
        tokenIndex++;
        token = ft_strtok(ptr, delimiters);
    }

    return commandList->length;
}
