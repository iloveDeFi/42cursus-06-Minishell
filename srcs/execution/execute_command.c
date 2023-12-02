#include "minishell.h"

void	ft_exec_cmd(t_command *cmd)
{
	t_env       *envList;
	if (cmd == NULL) {
        fprintf(stderr, "Error: Trying to execute a NULL command\n");
        return;
    }

	printf("Executing command: %s\n", cmd->name);

	int	init_stdout;
	int	init_stdin;

	init_stdout = dup(STDOUT_FILENO);
	init_stdin = dup(STDIN_FILENO);
	if (cmd->fdread >= 3)
		dup2(cmd->fdread, STDIN_FILENO);
	if (cmd->fdwrite >= 3)
		dup2(cmd->fdwrite, STDOUT_FILENO);
	if (ft_is_builtins(cmd) == 1)
		ft_exec_builtins(cmd,&envList);
	else if (ft_is_builtins(cmd) == 127)
		g_exit_code = 127;
	else
		ft_exec_external_code(cmd);
	if (cmd->fdread >= 3)
		close(cmd->fdread);
	if (cmd->fdwrite >= 3)
		close(cmd->fdwrite);
	dup2(init_stdout, STDOUT_FILENO);
	dup2(init_stdin, STDIN_FILENO);
	close(init_stdout);
	close(init_stdin);

	printf("Execution complete\n");
}

void	ft_exec_external_code(t_command *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("Error with fork");
		exit(EXIT_FAILURE); // Ajout d'une sortie anticipée en cas d'échec de fork
	}
	if (pid == 0)
	{
		ft_execute_external_command(cmd->name, cmd->args);
		perror("ft_execute_external_command"); // Modification ici
		exit(EXIT_FAILURE); // Utilisation d'une valeur d'échec standard
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
	}
}
