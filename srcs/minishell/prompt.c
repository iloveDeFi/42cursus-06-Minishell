#include "minishell.h"

void ft_custom_prompt_msg(t_mini *shell)
{
	if (shell->av != NULL)
		free(shell->av);
	shell->av = readline("\033[32mminishell$ \033[0m");
}