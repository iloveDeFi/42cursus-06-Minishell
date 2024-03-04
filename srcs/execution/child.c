#include "minishell.h"

void	ft_initialize_child_processes(t_command *currentCommand)
{
	int i;

	i = 0;
	while (i < currentCommand->number_of_pipes + 1)
	{
		currentCommand->child_pids[i] = -1;
		i++;
	}
}

// int ft_launch_child_processes(t_command *command) 
// {
//     int i = 0;
// 	pid_t pid;

//     while (i < command->number_of_pipes + 1)
//     {
//         // command->child_pids[i] = fork();
//         if (pid < 0)
//         {
//             perror("Error forking process while creating child process\n");
//             exit(EXIT_FAILURE);
//         }
//         else if (command->child_pids[i] == 0)
//         {
//             ft_configure_child_process(command);
// 			ft_execute_child_process(command->args[0], command->args, command->envp);
//         }
//         i++;
//     }
// 	return 0;
// }

void ft_execute_child_process(char *full_path, char **args, char **envp)
{
	// TO DO : if (access(token->cmd, X_OK) == 0) {} ??
    if (execve(full_path, args, envp) == -1) 
    {
        perror("Erreur lors de l'exécution de la commande in ft_execute_child_process\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

// void ft_wait_for_all_child_processes_to_end(t_command *command) 
// {
//     int i;

//     i = 0;
//     while (i < command->number_of_pipes + 1)
//     {
//         waitpid(command->child_pids[i], NULL, 0);
//         i++;
//     }
// }

void	ft_configure_child_process(t_command *command) 
{
	int	init_stdout;
	int	init_stdin;

	init_stdout = dup(STDOUT_FILENO);
	init_stdin = dup(STDIN_FILENO);
	if (command->fdread >= 3)
		dup2(command->fdread, STDIN_FILENO);
	if (command->fdwrite >= 3)
		dup2(command->fdwrite, STDOUT_FILENO);
	if (ft_is_builtin(command))
	// TO DO : add envList
		ft_execute_builtin(command);
	else
	ft_exec_external_code(command)
	if (command->fdread >= 3)
		close(command->fdread);
	if (command->fdwrite >= 3)
		close(command->fdwrite);
	dup2(init_stdout, STDOUT_FILENO);
	dup2(init_stdin, STDIN_FILENO);
	close(init_stdout);
	close(init_stdin);
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
		ft_exec_external_command(command);
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

// void ft_configure_child_process(t_command *command) 
// {
//     // Redirect input from previous pipe except for first command
//     if (command->pipe_index > 0) {
//         dup2(command->pipes[command->pipe_index - 1][0], STDIN_FILENO);
//         close(command->pipes[command->pipe_index - 1][0]);
//         close(command->pipes[command->pipe_index - 1][1]);
//     }

//     // Redirect output to next pipe
//     if (command->pipe_index < command->number_of_pipes - 1) {
//         dup2(command->pipes[command->pipe_index][1], STDOUT_FILENO);
//         close(command->pipes[command->pipe_index][0]);
//         close(command->pipes[command->pipe_index][1]);
//     }
//     // ft_close_pipes(command);
// }