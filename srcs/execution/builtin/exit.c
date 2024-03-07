#include "minishell.h"

void	ft_exit(t_command *command)
{
	int	exit_status;

	// ft_close(ms); // TODO free all the mallocs
	if (command->args[1] == NULL)
		exit_status = g_exit_code;
	else if (ft_isnumber(command->args[1]))
		exit_status = ft_atoi(command->args[1]);
	else
	{
		perror("exit\n");
		exit(EXIT_FAILURE);
	}
	if (exit_status < 0)
		exit_status = -exit_status;
	exit(exit_status % 256);
}
