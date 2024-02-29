#include "minishell.h"

int	ft_handle_command_execution(t_command *command, \
	t_commandList *commandList, t_env *envList, char **envp)
{
	if (ft_execute_single_command(command, commandList, envList, envp) != 0)
	{
		perror("Error executing command\n");
		ft_destroy_commandlist(commandList);
		return (1);
	}
	else
		return (0);
}

int	ft_execute_single_command(t_command *command, t_commandList *commandList, \
	t_env *envList, char **envp)
{
	if (command)
	{
		if (ft_is_builtin(command))
		{
			ft_execute_builtin(command, envList);
		}
		else if (command->name[0] == '.' || command->name[0] == '/')
		{
			ft_execute_command_with_path(command);
		}
		else
		{
			ft_execute_external_command(command, commandList, envp);
		}
	}
	return (0);
}

void	ft_execute_external_command(t_command *command, \
	t_commandList *commandList, char **envp)
{
	char	*full_path;
	pid_t	pid;

	full_path = ft_build_full_path(commandList);
	if (full_path != NULL)
	{
		pid = fork();
		if (pid == 0)
			ft_execute_child_process(full_path, command->args, envp);
		else if (pid == -1)
			exit(EXIT_FAILURE);
		else
		{
			ft_wait_for_all_child_processes_to_end(&pid, commandList->length);
			free(full_path);
		}
	}
	else
		printf("Command not found in PATH: %s\n", command->name);
}
