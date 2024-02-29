#include "minishell.h"

char	*ft_build_full_path(t_commandList *commandList)
{
	char	*path;

	path = getenv("PATH");
	return (ft_lookfor_command_and_build_path(path, commandList));
}

void	ft_execute_command_with_absolute_path(t_command *command)
{
	pid_t	child_pid;
	int		status;

	child_pid = fork();
	if (child_pid == -1)
		exit(EXIT_FAILURE);
	if (child_pid == 0)
	{
		if (execve(command->name, command->args, NULL) == -1)
			exit(EXIT_FAILURE);
	}
	else
		waitpid(child_pid, &status, 0);
}

void	ft_execute_command_with_relative_path(t_command *command)
{
	char	*current_path;
	char	*full_path;
	char	*path_ptr;
	char	*command_name;

	current_path = getcwd(NULL, 0);
	if (current_path == NULL)
		exit(EXIT_FAILURE);
	full_path = malloc(strlen(current_path) + strlen(command->name) + 2);
	if (full_path == NULL)
		exit(EXIT_FAILURE);
	path_ptr = full_path;
	while (*current_path != '\0')
	{
		*path_ptr = *current_path;
		path_ptr++;
		current_path++;
	}
	*path_ptr = '/';
	path_ptr++;
	command_name = command->name;
	while (*command_name != '\0')
	{
		*path_ptr = *command_name;
		path_ptr++;
		command_name++;
	}
	*path_ptr = '\0';
	if (access(full_path, X_OK) == 0)
	{
		if (execve(full_path, command->args, NULL) == -1)
			exit(EXIT_FAILURE);
	}
	else
		exit(EXIT_FAILURE);
	free(current_path);
	free(full_path);
}

void	ft_execute_command_with_path(t_command *command)
{
	if (command->name[0] == '/')
		ft_execute_command_with_absolute_path(command);
	else if (command->name[0] == '.')
		ft_execute_command_with_relative_path(command);
}

char	*ft_lookfor_command_and_build_path(char *path, \
	t_commandList *commandList)
{
	char		*token;
	char		fullpath[MAX_PATH_LENGTH];
	char		*originalpath;
	t_command	*currentcommand;

	originalpath = ft_strdup(path);
	token = ft_strtok((char *)originalpath, ":");
	while (token != NULL)
	{
		currentcommand = commandList->head;
		while (currentcommand != NULL)
		{
			ft_strcpy(fullpath, token);
			ft_strcat(fullpath, "/");
			ft_strcat(fullpath, currentcommand->name);
			if (access(fullpath, X_OK) == 0)
			{
				free(originalpath);
				return (ft_strdup(fullpath));
			}
			currentcommand = currentcommand->next;
		}
		token = ft_strtok(NULL, ":");
	}
	free(originalpath);
	return (NULL);
}
