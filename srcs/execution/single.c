#include "minishell.h"

void	ft_execute_single_command(t_command *cmd, char **envp, t_env *envList)
{
	int		original_stdin;
	int		original_stdout;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	if (cmd->fdread >= 3)
		dup2(cmd->fdread, STDIN_FILENO);
	if (cmd->fdwrite >= 3)
		dup2(cmd->fdwrite, STDOUT_FILENO);
	if (ft_is_builtin(cmd))
		g_exit_code = ft_execute_builtin(cmd, envList);
	else
		ft_execute_external_in_fork(cmd, envp);
	if (cmd->fdread >= 3)
		close(cmd->fdread);
	if (cmd->fdwrite >= 3)
		close(cmd->fdwrite);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
	close(original_stdin);
}

void	ft_execute_external_command(t_command *cmd, char **env)
{
	char	filepath[MAX_PATH_LENGTH];
	char	**splited_path;
	int		i;

	// char *argv[2];
	// argv[0] = "ls";
	// argv[1] = NULL;
	// execve("/usr/bin/ls",argv, NULL);
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
		ft_execute_external_command(command, command->envp); // revese the order of the arguments
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

void	ft_execute_external_in_fork(t_command *cmd, char **envp)
{
	pid_t	fork_pid;
	int     exit_code;

	fork_pid = fork();
	if (fork_pid == 0)
		ft_execute_external_command(cmd, envp);
	waitpid(fork_pid, &exit_code, 0);
	if (WIFEXITED(exit_code))
		g_exit_code = WEXITSTATUS(exit_code);
	if (WIFSIGNALED(exit_code))
		g_exit_code = 128 + WTERMSIG(exit_code);
}
