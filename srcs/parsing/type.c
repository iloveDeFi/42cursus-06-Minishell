#include "minishell.h"

int ft_token_is_pipe(char *token, t_command *currentCommand, int *total_pipes)
{
	printf("enter in ft_token_is_pipe\n");
	if (ft_strcmp(token, "|") == 0) {
            if (currentCommand != NULL) {
                currentCommand->has_pipe = TRUE;
				currentCommand->pipe_index = currentCommand->number_of_pipes;
        		currentCommand->number_of_pipes++;
				ft_initialize_pipes(currentCommand);
				ft_initialize_child_processes(currentCommand);
				total_pipes++;
            }
			return 1;
	}
	return 0;
}

// DO NOT handle commands without spaces as separator i.e. commande>output.txt
int ft_token_is_redirection(char *token, t_command *currentCommand, int *tokenIndex) 
{
    printf("enter in ft_token_is_redirection\n");
	char *nextToken;

    if (ft_strcmp(token, "<") == 0 || ft_strcmp(token, "<<") == 0 || ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0) 
	{
        if (currentCommand != NULL) {
            currentCommand->has_redirection = TRUE;
			currentCommand->redirection_info.type = NO_REDIRECTION;
            // Goal next token gonna be the filename currentCommand;
            nextToken = ft_strtok(NULL, " ");
            if (nextToken != NULL) {
                currentCommand->redirection_info.filename = nextToken;
				// Gonna use this for << earth sandwich
                currentCommand->redirection_info.delimiter = nextToken;
                (*tokenIndex)++;
            } else {
    			fprintf(stderr, "Error: Filename is missing after redirection in ft_token_is_redirection.\n");
                g_exit_code = 426;
				// No need to exit(EXIT_FAILURE);
            }
        }
        return 1;
    }
    return 0;
}
