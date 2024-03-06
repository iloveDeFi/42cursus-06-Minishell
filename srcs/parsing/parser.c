#include "minishell.h"

t_command *ft_parser(char * input, t_env *envList)
{
	t_command *commands = NULL;
	char **tokens;

	if(!ft_check_quotes(input))
	{
		printf(">\n");
		return NULL;
	}
	ft_remove_quotes(input);
	tokens = ft_tokenize_input_with_strtok(input); // TODO rename this function
	if (!ft_parse_tokens(&commands, tokens))
	{
		return NULL;
	}
	ft_token_is_a_quotes(input);
	ft_found_and_replace_usd(commands, envList);
	return commands;
}
