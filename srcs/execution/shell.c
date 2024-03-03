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

 void ft_execute_minishell(t_commandList *commandList, t_mini *shell, t_env *envList, char **envp)
{
	while (1)
	{
		// TO DO: ADD SIGNALS HERE
		ft_custom_prompt_msg(shell);
		if (shell->av && !ft_is_only_spaces(shell->av)) // If the input is not only spaces
		{
			ft_manage_history(shell, shell->av);
			if (ft_launch_parsing_and_execution(commandList, shell->av, envList, envp) != 0)
			{
				perror("Error executing minishell in ft_execute_minishell\n");
				// ? TODO free something?
				break;  // Quit the loop if an error occurs during execution
			}
		}
		// ft_check_empty_av_shell(shell);
		ft_destroy_current_shell(shell);
	}
}
