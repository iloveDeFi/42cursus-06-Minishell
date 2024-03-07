#include "minishell.h"

t_command	*ft_parser(char *input, t_env *envList)
{
	t_command	*commands;
	t_token		**tokens;

	commands = NULL;
	tokens = ft_tokenize(input);
	if (!tokens)
	{
		// ? TODO something to free?
		return (NULL);
	}
	ft_found_and_replace_usd(tokens, envList);
	if (!ft_parse_tokens(&commands, tokens))
	{
		// ? TODO something to free?
		return (NULL);
	}
	// ? TODO should the replace usd / quotes be done in the tokenize function instead?
	return (commands);
}
