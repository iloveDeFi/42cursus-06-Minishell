#include "minishell.h"

int ft_launch_parsing(t_mini *shell) 
{
	if (shell->av == NULL)
	{
		perror("av == NULL\n");
		exit(EXIT_FAILURE);
	}
	if (shell->av[0] == '\0')
	{
		perror("Hey, the shell argv is an empty string or a null pointer\n");
		exit(EXIT_FAILURE);
	}
	if (ft_is_only_spaces(shell->av))
	{
		ft_destroy_current_shell(shell);
		return 0;
	}
	return 1;
}
