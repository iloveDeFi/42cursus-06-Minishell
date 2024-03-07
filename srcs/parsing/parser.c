#include "minishell.h"

t_command *ft_parser(char * input, t_env *envList)
{
	t_command *commands = NULL;
	t_token **tokens;

	// if(!ft_check_quotes(input))
	// {
	// 	printf(">\n");
	// 	return NULL;
	// }
	// ft_remove_quotes(input);
	tokens = ft_tokenize(input);
	if (!tokens)
	{
		// ? TODO something to free?
		return NULL;
	}
	ft_found_and_replace_usd(tokens, envList);
	if (!ft_parse_tokens(&commands, tokens))
	{
		return NULL;
	}
	return commands;
}
