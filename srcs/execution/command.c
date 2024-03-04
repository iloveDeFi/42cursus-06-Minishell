#include "minishell.h"

int ft_launch_command_execution(t_command *command, t_commandList *commandList, t_env *envList, char **envp)
{
	printf("enter in ft_launch_command_execution\n");
	if (ft_execute_single_command(command, commandList, envList, envp) != 0) 
    {
    	perror("Error executing command\n");
    	ft_destroy_commandList(commandList);
    	return 1;
    }
	else 
		return 0;
}

int ft_execute_single_command(t_command *command, t_commandList *commandList, t_env *envList, char **envp) 
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
            ft_execute_external_command(command, commandList, envp);
        }
    }
    else 

    {
        // Gérer d'autres types de commandes si nécessaire
    }
    return  (0);
}

// Execute the external command in a child process
void ft_execute_external_command(t_command *command, t_commandList *commandList, char **envp) 
{
    char *full_path;
	int status;
	int i;
    
	(void)envp;
	i = 0;
	// TO DO : full_path not necessary ?
    full_path = ft_build_full_path(/*command->name, */commandList);

    if (full_path != NULL) 
    {
        command->child_pids[i] = fork();

        if (command->child_pids[i] == 0) 
        {
			ft_launch_child_processes(command);
        } else if (command->child_pids[i] == -1) 
        {
            perror("Erreur lors de la création du processus enfant");
            exit(EXIT_FAILURE);
        } else {
			waitpid(command->child_pids[i], &status, 0);
			if (WIFEXITED(status))
				g_exit_code = WEXITSTATUS(status);
            free(full_path);
        }
    } else {
        perror("Command not found in PATH in ft_execute_external_command\n");
        printf("Command not found in PATH: %s\n", command->name);
    }
}

void ft_printCommand(t_command *command) {
    if (command != NULL) {
        printf("Command Name: %s\n", command->name);
        printf("Command Data: %p\n", command->data);
        printf("Command Arguments:\n");
        for (int i = 0; i < command->argCount; ++i) {
            printf("  Argument %d: %s\n", i, command->args[i]);
        }
        printf("Argument Count: %d\n", command->argCount);
        printf("Redirect file is : %s\n", command->redirection_info.filename);
        printf("Redirect delimiter is : %s\n", command->redirection_info.delimiter);
        // printf("Pipe File Descriptors: %d, %d\n", command->fd[0], command->fd[1]);
        printf("Next Command: %p\n", (void *)command->next);
        printf("Previous Command: %p\n", (void *)command->prev);
        //printf("Token Type: %d\n", command->tokenType);
        //printf("Quote Type: %d\n", command->quoteType);
    } else {
        printf("Command is NULL\n");
    }
}
