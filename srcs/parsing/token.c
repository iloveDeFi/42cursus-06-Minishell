#include "minishell.h"

char *ft_change_strtok_delimiter(char *input) 
{
    char *delimiter;
	
	delimiter = " ";

    if (ft_check_if_pipe_in_string(input))
    {
        delimiter = " |";
    }
    return delimiter;
}

int ft_tokenize_input_with_strtok(t_commandList *commandList, char *input, char *delimiter) 
{
    char *token;
    char inputCopy[ft_strlen(input) + 1];
    int tokenIndex;
    char *ptr;
	t_command *currentCommand;

	delimiter = ft_change_strtok_delimiter(input);
    tokenIndex = 0;
    ft_strcpy(inputCopy, input);
    ptr = inputCopy;
    currentCommand = NULL;
    token = ft_strtok(inputCopy, delimiter);
    while (token != NULL) 
    {
        currentCommand = ft_process_token_command_or_argument(commandList, currentCommand, token, delimiter);
        tokenIndex++;
        token = ft_strtok(ptr, delimiter);
    }
    return commandList->length;
}