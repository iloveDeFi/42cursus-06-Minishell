#include "minishell.h"

void ft_process_input_redirection(t_command *command)
{
	printf("enter in ft_process_input_redirection\n");
    int input_fd;

	// TO DO 
	// use command ?
	(void)command;
	
	input_fd = open(command->redirection_info.filename, O_RDONLY);
    if (input_fd == -1) {
        perror("Erreur lors de l'ouverture du fichier en lecture");
        exit(EXIT_FAILURE);
    }

    if (dup2(input_fd, STDIN_FILENO) == -1) {
        perror("Erreur lors de la redirection de l'entrée standard");
		close(input_fd);
        exit(EXIT_FAILURE);
    }

    close(input_fd);
}

void ft_process_output_redirection(t_command *command)
{
	printf("enter in ft_process_output_redirection\n");
    int output_fd;
	
	// TO DO use command ?
	(void)command;

	output_fd = open(command->redirection_info.filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd == -1) {
        perror("Erreur lors de l'ouverture du fichier en écriture");
        exit(EXIT_FAILURE);
    }

    if (dup2(output_fd, STDOUT_FILENO) == -1) {
        perror("Erreur lors de la redirection de la sortie standard");
		close(output_fd);
        exit(EXIT_FAILURE);
    }

    close(output_fd);
}

void ft_process_append_redirection(t_command *command)
{
	printf("enter in ft_process_append_redirection\n");
	int output_fd;
	// TO DO use command ?
	(void)command;

    output_fd = open(command->redirection_info.filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (output_fd == -1) {
        perror("Erreur lors de l'ouverture du fichier en écriture (mode ajout)");
        exit(EXIT_FAILURE);
    }

    if (dup2(output_fd, STDOUT_FILENO) == -1) {
        perror("Erreur lors de la redirection de la sortie standard");
		close(output_fd);
        exit(EXIT_FAILURE);
    }

    close(output_fd);
}

// TO DO : loop with i 
void ft_process_here_doc_redirection(t_command *command) 
{
	printf("enter in ft_process_here_doc_redirection\n");
	int i;

	i = 0;
    if (pipe(command->pipes[i]) == -1) {
        perror("Erreur lors de la création du pipe");
        exit(EXIT_FAILURE);
    }
    command->child_pids[i] = fork();
    if (command->child_pids[i] == -1) {
        perror("Erreur lors du fork");
        exit(EXIT_FAILURE);
    }
    if (command->child_pids[i] == 0) {
        close(command->pipes[i][1]);
        dup2(command->pipes[i][0], STDIN_FILENO);
        // TO DO : ADD execution command in the child here 
        // ft_execute_command(command);
        close(command->pipes[i][0]);
        exit(EXIT_SUCCESS);
    } else {
        // parent here
        close(command->pipes[i][0]);

        // Écrire le délimiteur dans le pipe
		// TO DO : CORRECT BUG because redirection_info.delimiter is null 
		printf("BUG strlen of redirection_info.delimiter is : %s\n", command->redirection_info.delimiter);
		if (command->redirection_info.delimiter != NULL)
		{
			if (write(command->pipes[i][1], command->redirection_info.delimiter, ft_strlen(command->redirection_info.delimiter)) == -1) {
            	perror("Erreur lors de l'écriture dans le pipe");
            	close(command->pipes[i][1]);
            	exit(EXIT_FAILURE);
			}
        }
		else {
			perror("Error delimiteur is NULL in ft_process_here_doc_redirection");
        	exit(EXIT_FAILURE);
		}
        close(command->pipes[i][1]);
        waitpid(command->child_pids[i], NULL, 0);
    }
}

void ft_launch_redirection_execution(t_command *command) 
{
	printf("enter in ft_launch_redirection_execution\n");

	if (command->redirection_info.type != NO_REDIRECTION)
	{
		if (command->redirection_info.type == OUTPUT_REDIRECTION) {
        	ft_process_output_redirection(command);
   		} else if (command->redirection_info.type == APPEND_REDIRECTION) {
        	ft_process_append_redirection(command);
    	} else if (command->redirection_info.type == INPUT_REDIRECTION) {
        	ft_process_input_redirection(command);
    	} else if (command->redirection_info.type == HERE_DOC_REDIRECTION) {
        	ft_process_here_doc_redirection(command);
   		} else {
        	perror("Unexpected value in ft_launch_redirection_execution\n");
            ft_free_redirection_info(&command->redirection_info);
        	exit(EXIT_FAILURE);
    	}
	}
    else if (command->redirection_info.type == NO_REDIRECTION)
    {
        ft_free_redirection_info(&command->redirection_info);
        return;
    }
	ft_free_redirection_info(&command->redirection_info);
}
