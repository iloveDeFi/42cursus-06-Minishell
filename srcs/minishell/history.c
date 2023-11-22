#include "minishell.h"

void manage_history(t_mini *shell)
{
	add_history(shell->av);
	if (shell->fd_history == 0)
		shell->fd_history = open("./.history_cmd", O_APPEND | O_WRONLY);
	if (shell->fd_history == -1)
		printf("Error: open file failed");
	else
	{
		write(shell->fd_history, shell->av, ft_strlen(shell->av));
		write(shell->fd_history, "\n", 1);
	}
	init_errs(shell);
}