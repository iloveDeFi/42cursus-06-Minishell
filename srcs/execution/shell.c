#include "minishell.h"

void ft_exit_shell(t_mini *shell)
{
	if (shell != NULL)
	{
		if (shell->av != NULL)
			free(shell->av);
		if (shell->commands != NULL)
			ft_destroy_commandList(shell->commands);
	}
}


// TO DO RECHECK FUNCTION
void ft_initialize_environment(t_env **envList, char **env)
{
	int i;
	char **var_array;
	t_env *new_envList_node;

	i = 0;
	var_array = ft_env_duplicate(env);
	if (!envList || !var_array)
	{
		perror("Error: Invalid pointer or memory allocation failure in ft_initialize_environment()");
		exit(EXIT_FAILURE);
	}
	while (var_array[i])
	{
		new_envList_node = ft_create_node_for_envList(var_array[i]);
		ft_add_to_list(envList, new_envList_node);
		i++;
	}
	ft_free_array(var_array);
}


void ft_initialize_minishell(t_mini *shell)
{
	if (shell == NULL)
	{
		perror("Error initializing mini shell");
		exit(EXIT_FAILURE);
	}
	shell->av = NULL;
	shell->fd_history = 0;
	shell->stdin_fd = dup(STDIN_FILENO);
	shell->stdout_fd = dup(STDOUT_FILENO);
	shell->error = NULL;
	shell->commands = NULL;
}

/* void ft_execute_minishell(t_commandList *commandList, t_mini *shell, t_env *envList, char **envp)
{
	while (1)
	{
		// TO DO: ADD SIGNALS HERE
		ft_custom_prompt_msg(shell);
		if (shell->av == NULL)
		{
			printf("stop shell\n");
			break;
		}
		ft_manage_history(shell, shell->av);
		if (ft_check_if_only_spaces(shell->av) == TRUE)
		{
			ft_destroy_current_shell(shell);
			continue;
		}
		else if (ft_strcmp(shell->av, "") != 0)
		{
			ft_launch_parsing_and_execution(commandList, shell->av, envList, envp);
			ft_destroy_current_shell(shell);
		}
		ft_destroy_current_shell(shell);
	}
} */

t_command get_first_command(t_commandList *commandList)
{
	t_command *command;

	command = commandList->head;
	if (command == NULL)
	{
		perror("Error: commandList is empty in get_first_command\n");
		exit(EXIT_FAILURE);
	}
	return *command;
}

// #define RED "\033[0;31m"
// #define RESET "\033[0m"

void test_execute_cmd(t_command *command)
{
}
void test_execute_cmds(t_command *command)
{
}

void test_fill_commandList(t_commandList *commandList, char *input)
{
	t_command *command;

	// if (ft_tokenize_input_with_strtok(commandList, input)) //  >= 1)  // ? TODO check if >.. ?
	// {

	// }
	// ft_add_to_commandList(commandList, command);
}


void test_execute(t_commandList *commandList) // ! TODO replace commandList with command...
{
	// check if the next cmd is NULL
	// printf("\033[0;31m");
	t_command *command;

	command = commandList->head;
	// print all the commands :
	while (command != NULL)
	{
		printf("\tcommand->cmd = %s\n", command->name);
		command = command->next;
	}
	// if(command->next == NULL)
	// {
	// printf("1\n");
	// // test_execute_cmd(commandList->head);
	// 	// printf("1\n");
	// }
	// else
	// {
	// 	// printf(RED+"2\n"+RESET);

	// 	// test_execute_cmds(commandList->head);
	// }
}

void test_parse(t_commandList *commandList, char *input)
{
	// t_command *command;

    // command = NULL;
	// if (commandList == NULL || input == NULL) { // ? TODO is it really necessary?
    //     perror("Error: Invalid pointer to commandList or null input in ft_launch_parsing_and_execution()\n");
    //     return 1;
    // }
    ft_initialize_commandList(commandList);
	// TO DO : custom error manager
	// ft_launch_error_manager(commandList, command, input, envList);

	if (ft_tokenize_input_with_strtok(commandList, input) >= 1)
	{
		// command = commandList->head;
		// command->number_of_pipes = ft_count_number_of_pipes(input);
		// while (command != NULL)
		// {
		// 	ft_launch_pipe_execution(command);
		// 	ft_launch_redirection_execution(command);
		// 	ft_launch_command_execution(command, commandList, envList, envp);
		// 	command = command->next;
		// }

	 	// ft_destroy_commandList(commandList);
	}
	else
		perror("Hey, no token from input with strtok in ft_launch_parsing_and_execution.\n");
	return 0;
}

 void ft_execute_minishell(t_commandList *commandList, t_mini *shell, t_env *envList, char **envp)
{
	while (1)
	{
		// TO DO: ADD SIGNALS HERE
		ft_custom_prompt_msg(shell);
		if (shell->av && !ft_is_only_spaces(shell->av)) // If the input is not only spaces
		{
			// ft_manage_history(shell, shell->av); // we just need to call the add_history function
			add_history(shell->av);
			test_parse(commandList, shell->av);
			test_execute(commandList);

			// if (ft_launch_parsing_and_execution(commandList, shell->av, envList, envp) != 0)
			// {
			// 	perror("Error executing minishell in ft_execute_minishell\n");
			// 	// ? TODO free something?
			// 	break;  // Quit the loop if an error occurs during execution
			// }
		}
		// ft_check_empty_av_shell(shell);
		ft_destroy_current_shell(shell);
	}
}
