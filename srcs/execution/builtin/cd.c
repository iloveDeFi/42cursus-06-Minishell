#include "minishell.h"

int	cd(t_command *command)
{
	if (command == NULL || command->args == NULL || command->args[1] == NULL)
	{
		chdir(getenv("HOME"));
		return (0);
	}
	if (command->args[2] != NULL)
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	if (chdir(command->args[1]) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", \
			command->args[1]);
		return (1);
	}
	return (0);
}

// void	ft_process_cd_argument(t_command *command, char *arg)
// {
// 	command->args = malloc(2 * sizeof(char *));
// 	command->args[0] = ft_strdup(arg);
// 	command->args[1] = NULL;
// }
