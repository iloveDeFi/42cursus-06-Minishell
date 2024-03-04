#include "minishell.h"

int ft_tokenize_input_with_strtok(t_commandList *commandList, char *input)
{
    char *token;
    int tokenIndex;
    char inputCopy[ft_strlen(input) + 1];
    t_command *currentCommand;

    tokenIndex = 0;
    ft_strcpy(inputCopy, input);
    currentCommand = NULL;
	token = ft_strtok(inputCopy, " ");

	 while (token != NULL)
	 {
		// ft_handle_error(); TO DO SOON
        ft_token_is_pipe(token, currentCommand);
		ft_token_is_redirection(token, currentCommand, &tokenIndex);
		currentCommand = ft_process_token(commandList, currentCommand, token);
        printf("->name: %s, %d, args:\n", currentCommand->name, commandList->length);
        int j = 0;
        while (currentCommand->args[j] != NULL)
        {
            printf("\t\t%s\n", currentCommand->args[j]);
            j++;
        }
        token = ft_strtok(NULL, " ");
        tokenIndex++;
    }
    return commandList->length;
}
