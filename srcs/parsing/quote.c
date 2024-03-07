#include "minishell.h"

bool	ft_check_quotes(char *input)
{
	int	single_quotes;
	int	double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	while (*input)
	{
		if (*input == '\'')
			single_quotes++;
		else if (*input == '"')
			double_quotes++;
		input++;
	}
	if (single_quotes % 2 == 0 && double_quotes % 2 == 0)
		return (true);
	else
	{
		g_exit_code = 1;
		return (false);
	}
}
