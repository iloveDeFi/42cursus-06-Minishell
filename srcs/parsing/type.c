#include "minishell.h"

int ft_token_is_pipe(char *token, t_command *currentCommand, int *total_pipes)
{
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

int ft_token_is_redirection(char *token, t_command *currentCommand, int *tokenIndex)
{
	if (ft_strcmp(token, "<") == 0 || ft_strcmp(token, "<<") || ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>")== 0) 
	{
            if (currentCommand != NULL) {
                currentCommand->has_redirection = TRUE;
				// TO DO : Capturez le nom du fichier de redirection dans le token suivant et enregistrez-le dans currentCommand->redirectFile.
                // Gérez la redirection d'entrée ici (par exemple, lisez le nom du fichier)
				// Goal next token gonna be the filename currentCommand;
    			token = ft_strtok(NULL, " ");
				if (token != NULL) {
					currentCommand->redirection_info.filename = token;
       		 		tokenIndex++;
    			} else {
					perror("Error, filename is missing after redirection.\n");
        			exit(EXIT_FAILURE);
   			 	}
    		token = ft_strtok(NULL, " ");
    		tokenIndex++;
            }
			return 1;
	}
	return 0;
}
