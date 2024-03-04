#include "minishell.h"

int	ft_execute_single_command(t_command *command, t_env *envList, char **envp) 
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
            ft_execute_external_command(envp, command);
        }
    }
	return 0;
}

void	ft_execute_external_command(char **env, struct s_command *cmd)
{
	char	filepath[MAX_PATH_LENGTH];
	char	**splited_path;
	int		i;

	if (access(cmd->name, X_OK) == 0)
		execve(cmd->name, cmd->args, env);
	splited_path = ft_split_path(env);
	i = 0;
	while (splited_path && splited_path[i] != NULL)
	{
		ft_strcpy(filepath, splited_path[i]);
		ft_strcat(filepath, "/");
		ft_strcat(filepath, cmd->name);
		if (access(filepath, X_OK) == 0)
		{
			execve(filepath, cmd->args, env);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (splited_path)
		ft_free_split(splited_path);
	ft_putstr_fd(cmd->name, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
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
		ft_execute_external_command(command->envp, command);
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

void	ft_launch_execution(t_command *command)
{
	if (!command->next)
		ft_execute_single_command(command);
	else
		ft_execute_multi_commands(command);
}

// Execute the external command in a child process
// void	ft_execute_external_command(t_command *command, char **envp, t_env *envList) 
// {
// 	printf("ft_execute_external_command\n");
//     char *full_path;
// 	int status;
// 	pid_t pid;
    
// 	(void)envp;
//     full_path = ft_build_full_path(command);

//     if (full_path != NULL) 
//     {
//         pid = fork();

// 			if (pid < 0)
//         	{
//            		perror("Error forking process while creating child process\n");
//             	exit(EXIT_FAILURE);
//         	}
//         	else if (pid == 0)
//         	{
//             	ft_configure_child_process(command, envList);
// 				ft_execute_child_process(command, full_path, command->args, command->envp);
//         	}
//         	else if (pid == -1) 
//         	{
//            		perror("Erreur lors de la création du processus enfant");
//             	exit(EXIT_FAILURE);
//         	} 	
// 			else {
// 				waitpid(pid, &status, 0);
// 				if (WIFEXITED(status))
// 					g_exit_code = WEXITSTATUS(status);
//             	free(full_path);
//         	}
//     } else {
//         perror("Command not found in PATH in ft_execute_external_command\n");
//         printf("Command not found in PATH: %s\n", command->name);
//     }
// }

void	ft_execute_multi_commands(t_mini *mini)
{
	int					fd_pipe_read_tmp;
	int					fd_pipe[2];
	int					exit_status;
	pid_t				pid;
	struct s_command 	*cmd;

	cmd = ms->cmd;
	fd_pipe_read_tmp = 0;
	while (cmd)
	{
		pipe(fd_pipe);
		fork_pid = fork();
		if (fork_pid == 0)
		{
			prepare_fds(cmd, &fd_pipe_read_tmp, fd_pipe);
			ft_run_cmd(ms, cmd);
		}
		close_fds(cmd, &fd_pipe_read_tmp, fd_pipe);
		cmd = cmd->next;
	}
	while (waitpid(-1, &exit_status, 0) > 0)
		;
	handle_exit_status(exit_status);
}