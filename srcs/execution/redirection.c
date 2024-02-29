#include "minishell.h"

void ft_process_input_redirection(t_redirection_info redirection_info, t_command *command)
{
	printf("enter in ft_process_input_redirection\n");
    int input_fd;

	// TO DO 
	// use command ?
	(void)command;
	
	input_fd = open(redirection_info.filename, O_RDONLY);
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

void ft_process_output_redirection(t_redirection_info redirection_info, t_command *command)
{
	printf("enter in ft_process_output_redirection\n");
    int output_fd;
	
	// TO DO use command ?
	(void)command;

	output_fd = open(redirection_info.filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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

void ft_process_append_redirection(t_redirection_info redirection_info, t_command *command)
{
	printf("enter in ft_process_append_redirection\n");
	// TO DO use command ?
	(void)command;

    int output_fd = open(redirection_info.filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
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

void ft_process_here_doc_redirection(t_redirection_info redirection_info, t_command *command) 
{
	printf("enter in ft_process_here_doc_redirection\n");
    int pipe_fd[2];
    pid_t child_pid;

    // TO DO use command ?
    (void)command;

    if (pipe(pipe_fd) == -1) {
        perror("Erreur lors de la création du pipe");
        exit(EXIT_FAILURE);
    }
    child_pid = fork();
    if (child_pid == -1) {
        perror("Erreur lors du fork");
        exit(EXIT_FAILURE);
    }
    if (child_pid == 0) {
        close(pipe_fd[1]);
        dup2(pipe_fd[0], STDIN_FILENO);
        // TO DO : ADD execution command in the child here 
        // ft_execute_command(command);
        close(pipe_fd[0]);
        exit(EXIT_SUCCESS);
    } else {
        // parent here
        close(pipe_fd[0]);

        // Écrire le délimiteur dans le pipe
		// TO DO : CORRECT BUG because redirection_info.delimiter is null 
		printf("BUG strlen of redirection_info.delimiter is : %s\n", redirection_info.delimiter);
        if (write(pipe_fd[1], redirection_info.delimiter, ft_strlen(redirection_info.delimiter)) == -1) {
            perror("Erreur lors de l'écriture dans le pipe");
            close(pipe_fd[1]);
            exit(EXIT_FAILURE);
        }

        close(pipe_fd[1]);
        waitpid(child_pid, NULL, 0);
    }
}

void ft_launch_redirection_execution(t_command *command) 
{
	printf("enter in ft_launch_redirection_execution\n");
    t_redirection_info redirection_info;
	
	redirection_info = ft_parse_all_redirection(command->name);

	if (redirection_info.type != NO_REDIRECTION)
	{
		if (redirection_info.type == OUTPUT_REDIRECTION) {
        	ft_process_output_redirection(redirection_info, command);
   		} else if (redirection_info.type == APPEND_REDIRECTION) {
        	ft_process_append_redirection(redirection_info, command);
    	} else if (redirection_info.type == INPUT_REDIRECTION) {
        	ft_process_input_redirection(redirection_info, command);
    	} else if (redirection_info.type == HERE_DOC_REDIRECTION) {
        	ft_process_here_doc_redirection(redirection_info, command);
   		}
    	else if (redirection_info.type == NO_REDIRECTION)
			return;
		else {
        	perror("Unexpected value in ft_process_redirection_execution\n");
        	exit(EXIT_FAILURE);
    	}
	}
	ft_free_redirection_info(&redirection_info);
}
