#include "minishell.h"

static void	ft_execute_external_in_fork(t_command *cmd, char **envp)
{
	pid_t	fork_pid;
	int		exit_code;

	fork_pid = fork();
	if (fork_pid == 0)
		ft_execute_external_command(cmd, envp);
	waitpid(fork_pid, &exit_code, 0);
	if (WIFEXITED(exit_code))
		g_exit_code = WEXITSTATUS(exit_code);
	if (WIFSIGNALED(exit_code))
		g_exit_code = 128 + WTERMSIG(exit_code);
}

void	ft_execute_cmd(t_command *cmd, char **envp, t_env *envList)
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
