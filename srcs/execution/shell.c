#include "minishell.h"

void	ft_custom_prompt_msg(t_mini *shell)
{
	char	*input;
	char	*cwd;
	size_t	alloc_size;

	if (shell->av != NULL)
	{
		free(shell->av);
		shell->av = NULL;
	}
	ft_signals_init(ft_signals_handle_input);
	alloc_size = sizeof(*cwd) * MAXPATHLEN + \
		ft_strlen("\033[1;35m") + ft_strlen("\033[0m") + 3;
	cwd = malloc(alloc_size);
	ft_strcpy(cwd, "\033[1;35m");
	getcwd(cwd + ft_strlen("\033[1;35m"), MAXPATHLEN);
	ft_strcat(cwd, "\033[0m$ ");
	input = readline(cwd);
	free(cwd);
	ft_signals_init(ft_signals_handle_execution);
	if (input != NULL)
	{
		shell->av = ft_strdup(input);
		free(input);
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

void	ft_execute_minishell(t_mini *shell, t_env *envList, char **envp)
{
    while (1)
    {
        // TO DO: ADD SIGNALS HERE
        ft_custom_prompt_msg(shell);
        ft_check_empty_av_shell(shell); // TODO remove that when signals are added
        // ft_handle_only_spaces(shell);
        //ft_check_empty_av_shell(shell);
        if (shell->av && !ft_is_only_spaces(shell->av))
        {
		    add_history(shell->av);
            if (ft_launch_parsing_and_execution(shell, shell->av, envList, envp) != 0)
            {
                perror("Error executing minishell in ft_execute_minishell\n");
                break;  // Quit the loop if an error occurs during execution
            }
        }
        ft_destroy_current_shell(shell);
    }
}
