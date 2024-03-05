#include "minishell.h"

int ft_search_exit_arg_in_envList(t_command *command, t_env *envList)
{
	int g_exit_code;
	t_env *current_node;

	g_exit_code = 0;

	if (command->argCount == 1 && strcmp(*command->args, "exit") == 0)
	{
		return 0; // Pas besoin de rechercher dans envList si l'argument est "exit"
	}

	current_node = envList;

	while (current_node != NULL)
	{
		if (ft_strcmp(current_node->name, *command->args) == 0)
		{
			if (ft_check_exit_arg_value(current_node->value) != 0)
			{
				return -1; // Valeur invalide
			}
			g_exit_code = ft_atoi(current_node->value);
			return g_exit_code;
		}
		current_node = current_node->next;
	}

	return -2; // Argument "exit" non trouvé
}


int ft_check_exit_arg_value(char *value)
{
	int num;

	num = ft_atoi(value);
	if (num < 0 || num > 255) {
		return 1;
	}
	return 0;
}

// int ft_exit(t_command *command, t_env *envList)
// {
// 	int g_exit_code = 0;

// 	if (command->argCount == 1) // because the args start with the command name
// 	{
// 		exit(EXIT_SUCCESS);
// 	}
// 	else if (command->argCount == 1 && strcmp(*command->args, "exit") == 0)
// 	{
// 		g_exit_code = ft_search_exit_arg_in_envList(command, envList);

// 		if (g_exit_code == -1)
// 		{
// 			perror("Exit arg number wrong. Must be between 0 to 255\n");
// 			exit(EXIT_FAILURE);
// 		}
// 		else if (g_exit_code == -2)
// 		{
// 			perror("Sorry but exit argument not found in envList\n");
// 			exit(EXIT_FAILURE);
// 		}
// 		else
// 		{
// 			exit(g_exit_code);
// 		}
// 	}
// 	else
// 	{
// 		perror("Exit failed. Take your mass gainer shaker\n");
// 		exit(EXIT_FAILURE);
// 	}
// }

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
