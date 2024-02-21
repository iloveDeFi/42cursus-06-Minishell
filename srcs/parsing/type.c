#include "minishell.h"

int ft_token_is_pipe(char *token, t_command *currentCommand)
{
	if (ft_strcmp(token, "|") == 0) {
            if (currentCommand != NULL) {
                currentCommand->has_pipe = TRUE;
            }
			return 1;
	}
	return 0;
}

int ft_token_is_redirection_input(char *token, t_command *currentCommand)
{
	if (ft_strcmp(token, "<") == 0 || ft_strcmp(token, "<<") == 0) 
	{
            if (currentCommand != NULL) {
                currentCommand->has_redirection_input = TRUE;
                // Gérez la redirection d'entrée ici (par exemple, lisez le nom du fichier)
            }
			return 1;
	}
	return 0;
}

int ft_token_is_redirection_output(char *token, t_command *currentCommand)
{
	if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0) 
	{
            if (currentCommand != NULL) {
                currentCommand->has_redirection_output = TRUE;
                // Gérez la redirection de sortie ici (par exemple, lisez le nom du fichier)
            }
			return 1;
	}
	return 0;
}