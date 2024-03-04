#include "minishell.h"

void	ft_exit_shell(t_mini *shell)
{
    if (shell != NULL) 
    {
        if (shell->av != NULL)
            free(shell->av);
        if (shell->cmd != NULL)
            ft_destroy_commandList(shell->cmd);
    }
}

void ft_initialize_environment(t_env **envList, char **env)
{
	int		i;
	char	**var_array;
	t_env	*new_envlist_node;

	i = 0;
	var_array = ft_env_duplicate(env);
	if (!envList || !var_array)
	{
		perror("Error: Memory failure in ft_initialize_environment()");
		exit(EXIT_FAILURE);
	}
	while (var_array[i])
	{
		new_envlist_node = ft_create_node_for_envlist(var_array[i]);
		ft_add_to_list(envList, new_envlist_node);
		i++;
	}
	ft_free_array(var_array);
}

void	ft_initialize_minishell(t_mini *shell)
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
    shell->cmd = NULL;
}

 void ft_execute_minishell(t_mini *shell, t_env *envList, char **envp)
{
    while (1)
    {
        // TO DO: ADD SIGNALS HERE
        ft_custom_prompt_msg(shell);
        ft_check_empty_av_shell(shell);
		add_history(shell->av);
        ft_handle_only_spaces(shell);
        //ft_check_empty_av_shell(shell);
		ft_launch_parsing(shell);
		ft_launch_execution(shell);
        ft_destroy_current_shell(shell);
    }
}
