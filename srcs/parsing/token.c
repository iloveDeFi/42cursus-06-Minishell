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
        ft_token_is_pipe(token, &currentCommand, &total_pipes);
		ft_token_is_redirection_input(token, &currentCommand);
        if (ft_token_is_redirection_output(token, &currentCommand) != 0) 
		{
			// Goal next token gonna be the filename currentCommand;
			token = ft_strtok(NULL, " ");
			currentCommand->redirection_info.filename = token;
   			tokenIndex++;
        }
		currentCommand = ft_process_token(&commandList, &currentCommand, token);
        token = ft_strtok(NULL, " ");
        tokenIndex++;
    }
    return commandList->length;
}

