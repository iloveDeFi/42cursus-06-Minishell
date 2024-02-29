#include "minishell.h"

void	ft_manage_history(t_mini *shell, const char *input)
{
	size_t	input_len;
	char	*input_copy;

	if (shell->fd_history == -1)
	{
		shell->fd_history = open("./.history_cmd", O_APPEND | O_WRONLY);
		if (shell->fd_history == -1)
			return ;
	}
	if (input != NULL)
	{
		input_len = ft_strlen(input);
		input_copy = ft_strdup(input);
		if (input_copy == NULL)
		{
			perror("Erreur d'allocation de mémoire");
			return ;
		}
		add_history(input_copy);
		write(shell->fd_history, input_copy, input_len);
		write(shell->fd_history, "\n", 1);
		free(input_copy);
	}
}

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
