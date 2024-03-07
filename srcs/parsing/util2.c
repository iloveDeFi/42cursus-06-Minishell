#include "minishell.h"

void	ft_error_free_toks(t_token **tokens)
{
	ft_putstr_fd("Error: unclosed quote\n", STDERR_FILENO);
	ft_free_tokens(tokens);
}
