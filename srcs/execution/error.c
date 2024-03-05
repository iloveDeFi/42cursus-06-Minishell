#include "minishell.h"

bool	ft_is_only_spaces(const char *str)
{
	while (*str)
	{
		if (*str != ' ')
		{
			return (false);
		}
		str++;
	}
	return (true);
}

void	ft_handle_only_spaces(t_mini *shell)
{
	if (ft_is_only_spaces(shell->av))
	{
		ft_destroy_current_shell(shell);
		return ;
	}
}

void	ft_check_null_av_shell(t_mini *shell)
{
	if (shell->av == NULL)
	{
		perror("av == NULL\n");
		exit(EXIT_FAILURE);
	}
}

void	ft_check_empty_av_shell(t_mini *shell)
{
	if (shell->av == NULL || shell->av[0] == '\0')
	{
		perror("The shell argv is an empty string or a null pointer\n");
		exit(EXIT_FAILURE);
	}
}
