#include "minishell.h"

void	ft_configure_child_process(t_command *command, t_env *envList) 
{
	printf("Enter in ft_configure_child_process\n");
	int	init_stdout;
	int	init_stdin;

	init_stdout = dup(STDOUT_FILENO);
	init_stdin = dup(STDIN_FILENO);
	if (command->fdread >= 3)
		dup2(command->fdread, STDIN_FILENO);
	if (command->fdwrite >= 3)
		dup2(command->fdwrite, STDOUT_FILENO);
	if (ft_is_builtin(command))
		ft_execute_builtin(command, envList);
	// else
	// ft_exec_external_code(command);
	if (command->fdread >= 3)
		close(command->fdread);
	if (command->fdwrite >= 3)
		close(command->fdwrite);
	dup2(init_stdout, STDOUT_FILENO);
	dup2(init_stdin, STDIN_FILENO);
	close(init_stdout);
	close(init_stdin);
}

void ft_execute_child_process(t_command *command, char *full_path, char **args, char **envp)
{
	printf("Enter in ft_execute_child_process\n");
	if (access(command->name, X_OK) == 0)
	{
		if (execve(full_path, args, envp) == -1) 
    	{
       		perror("Erreur lors de l'exécution de la commande in ft_execute_child_process\n");
        	exit(EXIT_FAILURE);
    	}
	}
    exit(EXIT_SUCCESS);
}

void ft_configure_parent_process(t_command *command)
{
    if (command->fdwrite >= 3) // TO DO : check this line
	{
        if (dup2(command->fdread, STDIN_FILENO) == -1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(command->fdwrite);
        close(command->fdread);
    }
}
