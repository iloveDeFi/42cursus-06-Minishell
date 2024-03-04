#include "minishell.h"

int ft_launch_command_execution(t_command *command, t_commandList *commandList, t_env *envList, char **envp)
{
	printf("enter in ft_launch_command_execution\n");
	if (ft_execute_single_command(command, envList, envp) != 0) 
    {
    	perror("Error executing command\n");
    	ft_destroy_commandList(commandList);
    	return 1;
    }
	else 
		return 0;
}

int ft_execute_single_command(t_command *command, t_env *envList, char **envp) 
{
    if (command) 
    {
        if (ft_is_builtin(command)) 
        {
            printf("Built-in found. Launch execute builtin of command: %s\n", command->name);
            ft_execute_builtin(command, envList);
        } 
        else if (command->name[0] == '.' || command->name[0] == '/') 
        {
            printf("Relative or absolute path detected. Command: %s\n", command->name);
            ft_execute_command_with_path(command);
        } 
        else 
        {
            printf("External command detected. Command: %s\n", command->name);
			// TO DO : fork hre
            ft_execute_external_command(command, envp, envList);
        }
    }
	return 0;
}

// Execute the external command in a child process
void ft_execute_external_command(t_command *command, char **envp, t_env *envList) 
{
	printf("ft_execute_external_command\n");
    char *full_path;
	int status;
	pid_t pid;
    
	(void)envp;
    full_path = ft_build_full_path(command);

    if (full_path != NULL) 
    {
        pid = fork();

			if (pid < 0)
        	{
           		perror("Error forking process while creating child process\n");
            	exit(EXIT_FAILURE);
        	}
        	else if (pid == 0)
        	{
            	ft_configure_child_process(command, envList);
				ft_execute_child_process(command, full_path, command->args, command->envp);
        	}
        	else if (pid == -1) 
        	{
           		perror("Erreur lors de la création du processus enfant");
            	exit(EXIT_FAILURE);
        	} 	
			else {
				waitpid(pid, &status, 0);
				if (WIFEXITED(status))
					g_exit_code = WEXITSTATUS(status);
            	free(full_path);
        	}
    } else {
        perror("Command not found in PATH in ft_execute_external_command\n");
        printf("Command not found in PATH: %s\n", command->name);
    }
}

void	ft_exec_external_code(t_command *command)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		perror("Error with fork");
	if (pid == 0)
	{
		ft_execute_external_command(command, command->envp, command->envList);
		perror("execve");
		exit(errno);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
	}
}
