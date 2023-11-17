#include "minishell.h"

/*void    ft_execute_command(t_command *command)
{
    pid_t   child_pid;
    int     status;

    child_pid = fork();
    if (child_pid < 0)
        perror("[ERROR] : Fork error\n");
    if (child_pid == 0)
    {
        execvp(command->name, command->arguments);
        perror("[ERROR] : Execution command\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(child_pid, &status, 0);
        if (WIFEXITED(status))
        {    
            printf("%d\n", WIFEXITED(status));
        }
    }
}*/

void	exec_cmd(t_command *cmd)
{
	int	init_stdout;
	int	init_stdin;

	init_stdout = dup(STDOUT_FILENO);
	init_stdin = dup(STDIN_FILENO);
	if (cmd->fdread >= 3)
		dup2(cmd->fdread, STDIN_FILENO);
	if (cmd->fdwrite >= 3)
		dup2(cmd->fdwrite, STDOUT_FILENO);
	if (is_builtins(cmd) == 1)
		exec_builtins(cmd);
	else if (is_builtins(cmd) == 127)
		g_exit_code = 127;
	else
		exec_external_code(cmd);
	if (cmd->fdread >= 3)
		close(cmd->fdread);
	if (cmd->fdwrite >= 3)
		close(cmd->fdwrite);
	dup2(init_stdout, STDOUT_FILENO);
	dup2(init_stdin, STDIN_FILENO);
	close(init_stdout);
	close(init_stdin);
}

void	exec_external_code(t_command *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		perror("Error with fork");
	if (pid == 0)
	{
		exec_external(cmd);
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
