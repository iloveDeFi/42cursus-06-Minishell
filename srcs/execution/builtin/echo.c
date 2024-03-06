#include "minishell.h"

int	echo(t_command *cmd)
{
	int			i;
	int			suppressnewline;

	i = 1;
	suppressnewline = 0;
	if (cmd == NULL || cmd->args == NULL)
	{
		write(STDERR_FILENO, "An error occurred: not enough arguments\n", 41);
		return (1);
	}
	if (cmd->args[1] && strcmp(cmd->args[1], "-n") == 0)
	{
		suppressnewline = 1;
		i++;
	}
	while (cmd->args[i] != NULL)
	{
		write(STDOUT_FILENO, cmd->args[i], strlen(cmd->args[i]));
		if (cmd->args[i + 1] != NULL)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (!suppressnewline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
