#include "minishell.h"

void	ft_custom_prompt_msg(t_mini *shell)
{
	char	*input;

	if (shell->av != NULL)
	{
		free(shell->av);
		shell->av = NULL;
	}
	ft_signals_init(ft_signals_handle_input);
	input = readline("\033[1;35mminishell$ \033[0m");
	ft_signals_init(ft_signals_handle_execution);
	if (input != NULL)
	{
		shell->av = ft_strdup(input);
		free(input);
	}
}
