#include "minishell.h"

static int	token_count(char *input)
{
	int	count;
	int	i;
	char	in_quote;

	in_quote = 0;
	count = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (in_quote == 0)
				in_quote = input[i];
			else if (in_quote == input[i])
				in_quote = 0;
		}
		if (input[i] == ' ' && in_quote == 0)
			count++;
		i++;
	}
	return (count + 1);
}


static void	set_is_in_quote(char c, char *in_quote)
{
    printf("entering set_is_in_quote\n");
	if (c == '\'' || c == '"')
	{
		if (*in_quote == 0)
			*in_quote = c;
		else if (*in_quote == c)
			*in_quote = 0;
	}
}

static void	add_token(t_token **tokens, int *token_index, char *input, int *start, int end)
{
	char	in_quote;
	t_token	*token;

	// move all spaces
	// while (input[*start] == ' ' && *start < end)
	// 	{(*start)++;
	// 	printf("a\n");
	// 	}
	if (*start == end)
	{
		(*start)++;
		return ;
	}

	in_quote = 0;
	if ((input[*start] == '"' || input[*start] == '\'') && input[*start] == input[end-1])
	{
		in_quote = input[*start];
		(*start)++;
	}
	// ! TODO if not in quote, replace the $var
	token = (t_token *)malloc(sizeof(t_token));
	token->word = ft_substr(input, *start, end - *start - (in_quote!=0));
	token->is_in_quote = in_quote;
	tokens[*token_index] = token;
	// tokens[*token_index] = ft_substr(input, *start, end - *start);
	(*token_index)++;
	*start = end + 1;

}

void	ft_free_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		free(tokens[i]->word);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

t_token	**ft_tokenize(char *input)
{
	t_token	**tokens;
	int		token_index;
	int		start;
	int		end;
	char	in_quote;

	tokens = (t_token **)malloc(sizeof(t_token *) * (token_count(input) + 1));
	token_index = 0;
	start = 0;
	end = 0;
	in_quote = 0;
	while (input[end])
	{
		set_is_in_quote(input[end], &in_quote);
		if (input[end] == ' ' && in_quote == 0)
			add_token(tokens, &token_index, input, &start, end);
		end++;
	}
	add_token(tokens, &token_index, input, &start, end);
	tokens[token_index] = NULL;
	int i = 0;
	while (tokens[i] != NULL)
	{
		printf("tokens[%d] = %s\n", i, tokens[i]->word);
		i++;
	}
	if (in_quote != 0)
	{
		ft_putstr_fd("Error: unclosed quote\n", STDERR_FILENO);
		ft_free_tokens(tokens);
		return (NULL);
	}
	return (tokens);

}

static t_command	*ft_create_new_command(t_token **tokens, int arg_len, int fdwrite, int fdread)
{
	t_command *command;
	int token_index;
	int args_index;

	token_index = 0;
	args_index = 0;
	command = (t_command *)malloc(sizeof(t_command));
	if (ft_is_redirection(tokens[token_index]->word))// skip the redirection and the filename (possibility to put those 2 lines in 1) : token_index += 2*ft_is_redirection(tokens[token_index])
		token_index += 2;
	command->name = ft_strdup(tokens[token_index]->word);
	command->args = (char **)malloc(sizeof(char *) * (arg_len + 2));
	command->argCount = 0;
	while(token_index < arg_len + 1)
	{
		if (ft_is_redirection(tokens[token_index]->word))// skip the redirection and the filename
		{
			token_index += 2;
			continue;
		}
		command->args[args_index] = ft_strdup(tokens[token_index]->word);
		args_index++;
		token_index++;
	}
    command->argCount = args_index;
	command->args[args_index] = NULL;
	command->next = NULL;
	command->fdread = fdread;
	command->fdwrite = fdwrite;
	command->end_of_file = NULL;
	return command;
}

bool	ft_parse_tokens(t_command **commands, t_token **tokens)
{
	int tokenIndex;
	int fdwrite;
	int fdread;

	tokenIndex = 0;
	fdwrite = 1;
	fdread = 1;
	while (tokens[tokenIndex] != NULL)
	{
		if (ft_is_redirection(tokens[tokenIndex]->word))
		{	
			if (ft_parse_all_redirection(tokens[tokenIndex]->word, tokens[tokenIndex + 1]->word, &fdread, &fdwrite) == false)
				return false;
		}
		else if (tokens[tokenIndex + 1] == NULL || ft_strcmp(tokens[tokenIndex + 1]->word, "|") == 0)
		{
            ft_command_add_back(commands, ft_create_new_command(tokens, tokenIndex, fdwrite, fdread));
            tokens += tokenIndex + 1 + (tokens[tokenIndex + 1] != NULL); // bidouillage, pour skip le pipe
			tokenIndex = -1; // -1 so that it becomes 0 after the incrementation
			fdwrite = 1;
			fdread= 0;
		}
		else if(ft_strcmp(tokens[tokenIndex + 1]->word, "<<") == 0) // ! TODO do that in ft_parse_all_redirection..?
		{
			ft_command_add_back(commands, ft_create_new_command(tokens, tokenIndex, fdwrite, fdread));
		}
		tokenIndex++;
	}
	return (true);
}
