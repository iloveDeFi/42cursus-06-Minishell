#include "minishell.h"

void	ft_exec_cmd(t_command *cmd, t_env *envList)
{
	int		init_stdout;
	int		init_stdin;

	if (cmd == NULL)
	{
		fprintf(stderr, "Error: Trying to execute a NULL command\n");
		return ;
	}
	printf("Executing command: %s\n", cmd->name);
	init_stdout = dup(STDOUT_FILENO);
	init_stdin = dup(STDIN_FILENO);
	if (cmd->fdread >= 3)
		dup2(cmd->fdread, STDIN_FILENO);
	if (cmd->fdwrite >= 3)
		dup2(cmd->fdwrite, STDOUT_FILENO);
	if (ft_is_builtins(cmd) == 1)
		ft_exec_builtins(cmd, &envList);
	else if (ft_is_builtins(cmd) == 127)
		g_exit_code = 127;
	else
		ft_exec_external_code(cmd, envList);
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

void ft_exec_external_code(t_command *cmd, t_env *envList)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("Error with fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        if (cmd->fdwrite >= 3)
        {
            if (dup2(cmd->fdwrite, STDOUT_FILENO) == -1)
            {
                perror("Error redirecting STDOUT_FILENO");
                exit(EXIT_FAILURE);
            }
        }
        if (cmd->fdread >= 3)
        {
            if (dup2(cmd->fdread, STDIN_FILENO) == -1)
            {
                perror("Error redirecting STDIN_FILENO");
                exit(EXIT_FAILURE);
            }
        }
        close(cmd->fdread);
        close(cmd->fdwrite);

        char *executable_path = find_executable_path(cmd->name, envList);
        if (executable_path != NULL)
        {
            printf("Executing external command:\n");
            printf("Command to execute: %s\n", executable_path);
            for (int i = 0; cmd->args[i] != NULL; i++)
                printf("Argument %d: %s\n", i, cmd->args[i]);
            printf("Test avant EXEC\n");

            if (execve(executable_path, cmd->args, NULL) == -1)
            {
                perror("Error during external command execution");
                exit(EXIT_FAILURE);
            }
            free(executable_path);
        }
        else
        {
            fprintf(stderr, "Error: Executable not found in PATH\n");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        printf("Child process created with PID: %d\n", pid);

        waitpid(pid, &status, 0);

        if (WIFEXITED(status))
        {
            int exitStatus = WEXITSTATUS(status);
            printf("Le processus enfant s'est terminé avec le code de sortie : %d\n", exitStatus);
        }
        else if (WIFSIGNALED(status))
        {
            int signalNumber = WTERMSIG(status);
            printf("Le processus enfant a été interrompu par le signal : %d\n", signalNumber);
        }
    }
}

void ft_execute_external_command(char *cmdPath, char *args[], t_env *envList)
{
    char *full_path = find_executable_path(cmdPath, envList);

    if (full_path != NULL)
    {
        pid_t pid;
        int status;

        pid = fork();

        if (pid == 0)
        {
            if (execve(full_path, args, NULL) == -1)
            {
                perror("Erreur lors de l'exécution de la commande");
                exit(EXIT_FAILURE);
            }
        }
        else if (pid == -1)
        {
            perror("Erreur lors de la création du processus enfant");
            exit(EXIT_FAILURE);
        }
        else
        {
            waitpid(pid, &status, 0);

            if (WIFEXITED(status))
            {
                int exitStatus = WEXITSTATUS(status);
                printf("Le processus enfant s'est terminé avec le code de sortie : %d\n", exitStatus);
            }
            else if (WIFSIGNALED(status))
            {
                int signalNumber = WTERMSIG(status);
                printf("Le processus enfant a été interrompu par le signal : %d\n", signalNumber);
            }

            free(full_path);
        }
    }
    else
    {
        fprintf(stderr, "Command not found in PATH: %s\n", cmdPath);
    }
}
