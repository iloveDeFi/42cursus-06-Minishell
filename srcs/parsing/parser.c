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
<<<<<<< HEAD
	ft_token_is_a_quotes(input);
	ft_found_and_replace_usd(commands, envList);
=======
	// ft_parse_all_redirection(*tokens);
	// ? TODO should the replace usd / quotes be done in the tokenize function instead?
	// ft_token_is_a_quotes(input);
	// ft_found_and_replace_usd(commands, envList);
>>>>>>> main
	return commands;
}
