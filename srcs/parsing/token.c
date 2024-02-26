#include "minishell.h"

int ft_tokenize_input_with_strtok(t_commandList *commandList, char *input) 
{
    char *token;
    int tokenIndex;
    char inputCopy[ft_strlen(input) + 1];
    t_command *currentCommand;
	int total_pipes;
    
    tokenIndex = 0;
	total_pipes = 0;
    ft_strcpy(inputCopy, input);
    currentCommand = NULL;
	token = ft_strtok(inputCopy, " ");

	 while (token != NULL) {
		// ft_handle_error(); TO DO SOON
        ft_token_is_pipe(token, currentCommand, &total_pipes);
		ft_token_is_redirection(token, currentCommand, &tokenIndex);
		currentCommand = ft_process_token(commandList, currentCommand, token);
        token = ft_strtok(NULL, " ");
        tokenIndex++;
    }
    return commandList->length;
}

