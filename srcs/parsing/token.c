#include "minishell.h"

char **	ft_tokenize_input_with_strtok(char *input) // TODO rename
{
	return(ft_split(input, ' '));
}

static t_command	*ft_create_new_command(char **tokens, int arg_len, int fdwrite, int fdread)
{
	t_command *command;
	int token_index;
	int args_index;

	token_index = 0;
	args_index = 0;
	command = (t_command *)malloc(sizeof(t_command));
	if (ft_is_redirection(tokens[token_index]))// skip the redirection and the filename (possibility to put those 2 lines in 1) : token_index += 2*ft_is_redirection(tokens[token_index])
		token_index += 2;
	command->name = ft_strdup(tokens[token_index]);
	command->args = (char **)malloc(sizeof(char *) * (arg_len + 2));
	command->argCount = 0;
	while(token_index < arg_len + 1)
	{
		if (ft_is_redirection(tokens[token_index]))// skip the redirection and the filename
		{
			token_index += 2;
			continue;
		}
		command->args[args_index] = ft_strdup(tokens[token_index]);
		args_index++;
		token_index++;
	}
    command->argCount = args_index;
	command->args[args_index] = NULL;
	command->next = NULL;
	command->fdread = fdread;
	command->fdwrite = fdwrite;
	command->end_of_file = NULL;
	// command->redirection_info.filename = NULL;
	// command->redirection_info.delimiter = NULL;
	// command->redirection_info.type = NO_REDIRECTION;
	// printf("-- command->redirection_info.type = NO_REDIRECTION : %d\n", command->redirection_info.type);
	// printf("arg_len = %d\n", arg_len);
	// printf("name = %s\n", command->name);
	// i = 0;
	// while(command->args[i] != NULL)
	// {
	// 	printf("args = %s\n", command->args[i]);
	// 	i++;
	// }

	return command;
}

bool	ft_parse_tokens(t_command **commands, char **tokens)
{
	int tokenIndex;
	int fdwrite;
	int fdread;

	tokenIndex = 0;
	fdwrite = 1;
	fdread = 1;
	while (tokens[tokenIndex] != NULL)
	{
		if (ft_is_redirection(tokens[tokenIndex]))
		{	
			if (ft_parse_all_redirection(tokens[tokenIndex], tokens[tokenIndex + 1], &fdread, &fdwrite) == false)
				return false;
		}
		else if (tokens[tokenIndex + 1] == NULL || ft_strcmp(tokens[tokenIndex + 1], "|") == 0)
		{
			ft_command_add_back(commands, ft_create_new_command(tokens, tokenIndex, fdwrite, fdread));
			tokens += tokenIndex + 1 + (tokens[tokenIndex + 1] != NULL); // bidouillage, pour skip le pipe
			tokenIndex = -1; // -1 so that it becomes 0 after the incrementation
			fdwrite = 1;
			fdread= 0;
		}
		else if(ft_strcmp(tokens[tokenIndex + 1], "<<") == 0)
		{
			// TO DO : use tokens[tokenIndex + 2]) as EOF
			printf("tokens[tokenIndex + 2] = %s\n", tokens[tokenIndex + 2]);
			(*commands)->end_of_file = ft_strdup(tokens[tokenIndex + 2]); // NOPE
			// (*commands)->end_of_file = malloc(sizeof(char) * word_len((*tokens), (*commands)->i));// NOPE
			// (*commands)->end_of_file = malloc(sizeof(char) * word_len(input, new->i));// NOPE
			// (*commands)->end_of_file = get_filename((*commands), (*tokens));// NOPE
			ft_command_add_back(commands, ft_create_new_command(tokens, tokenIndex, fdwrite, fdread));
			ft_exec_heredoc(*commands);
		}
		tokenIndex++;
	}
	return (true);
}
