#include "minishell.h"

int	ft_tokenize_input_with_strtok(t_commandList *commandList, char *input)
{
	char		*token;
	char		inputcopy[ft_strlen(input) + 1];
	t_command	*currentcommand;

	ft_strcpy(inputcopy, input);
	currentcommand = NULL;
	token = ft_strtok(inputcopy, " | < << > >>\"");
	while (token != NULL)
	{
		currentcommand = ft_process_token(commandList, currentcommand, token);
		token = ft_strtok(NULL, " | < << > >>\"");
	}
	return (commandList->length);
}
