#include "minishell.h"

void ft_custom_prompt_msg(t_mini *shell)
{
	if (shell->argv != NULL)
		free(shell->argv);
	shell->argv = readline("\033[32mminishell$ \033[0m");
}