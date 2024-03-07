#include "minishell.h"

static int	token_count(char *input)
{
	int		count;
	int		i;
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
	if (c == '\'' || c == '"')
	{
		if (*in_quote == 0)
			*in_quote = c;
		else if (*in_quote == c)
			*in_quote = 0;
	}
}

static void	add_token(t_token **tokens, int *token_index, char *input, \
	int word_index[2])
{
	char	in_quote;
	t_token	*token;

	if (word_index[0] == word_index[1])
	{
		(word_index[0])++;
		return ;
	}
	in_quote = 0;
	if ((input[word_index[0]] == '"' || input[word_index[0]] == '\'') && \
		input[word_index[0]] == input[word_index[1] -1])
	{
		in_quote = input[word_index[0]];
		(word_index[0])++;
	}
	token = (t_token *)malloc(sizeof(t_token));
	token->word = ft_substr(input, word_index[0], \
		word_index[1] - word_index[0] - (in_quote != 0));
	token->is_in_quote = in_quote;
	tokens[*token_index] = token;
	(*token_index)++;
	word_index[0] = word_index[1] + 1;
}

//word_index[0] = start
//word_index[1] = end
//word_index[2] = i
//word_index[3] = token_index

t_token	**ft_tokenize(char *input)
{
	t_token	**tokens;
	char	in_quote;
	int		word_index[4];

	ft_set_array_to_zero(word_index, 4);
	tokens = (t_token **)malloc(sizeof(t_token *) * (token_count(input) + 1));
	in_quote = 0;
	while (input[word_index[1]])
	{
		set_is_in_quote(input[word_index[1]], &in_quote);
		if (input[word_index[1]] == ' ' && in_quote == 0)
			add_token(tokens, &word_index[3], input, word_index);
		word_index[1]++;
	}
	add_token(tokens, &word_index[3], input, word_index);
	tokens[word_index[3]] = NULL;
	while (tokens[word_index[2]] != NULL)
		word_index[2]++;
	if (in_quote != 0)
	{
		ft_error_free_toks(tokens);
		return (NULL);
	}
	return (tokens);
}
