/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienbelda <julienbelda@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:45:17 by bat               #+#    #+#             */
/*   Updated: 2023/11/28 20:27:09 by julienbelda      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exit_shell(t_mini *shell)
{
    if (shell->av)
        free(shell->av);
}

//before calling function set head and tail to NULL and length to 0
/*void ft_initialize_environment(t_envList *envList, char **env)
{
    int i;
    char **var_array;
    t_env *newNode;

    newNode = NULL;
    var_array = ft_env_duplicate(env);
    i = 0;
    while (var_array[i])
    {
        newNode = ft_createNode(var_array[i]);
        if (!envList)
            envList = &newNode;
        else 
            appendToList(envList, newNode);
        i++;
    }
    free_array(var_array);
}*/

/*void ft_initialize_environment(t_envList *envList, char **env)
{
    int i;
    char **var_array;
    t_node *newNode;  // Modifier le type de newNode pour t_node

    envList->head = NULL;  // Assurez-vous que envList->head est initialisé à NULL
    var_array = ft_env_duplicate(envList);
    i = 0;
    while (var_array[i])
    {
        newNode = ft_createNode(var_array[i]);
        appendToList(&(envList->head), newNode);  // Passez l'adresse de envList->head
        i++;
    }
    free_array(var_array);
}*/

void	ft_initialize_environment(t_env **envlist, char **env)
{
	t_env	*new_node;
	char	**var_array;
	int		i;

	new_node = NULL;
	var_array = ft_env_duplicate(env);
	i = 0;
	while (var_array[i])
	{
		new_node = create_node(var_array[i]);
		if (!envlist)
			envlist = &new_node;
		else
			add_to_list(envlist, new_node);
		i++;
	}
	free_array(var_array);
}

void ft_initialize_minishell(t_mini *shell, t_env **env)
{
    *env = NULL;
    shell->av = NULL;
    shell->numberOfCommands = 0;
    shell->fd_history = 0;
    shell->status = 0;
    shell->stdin_fd = dup(STDIN_FILENO);
    shell->stdout_fd = dup(STDOUT_FILENO);
    shell->commands = NULL;
    shell->child = malloc(sizeof(t_global));
    if (shell->child == NULL) {
        perror("Failed to allocate memory for shell->child");
        exit(EXIT_FAILURE);
    }
    shell->exec = malloc(sizeof(t_global));  // Initialisez-le de la même manière si nécessaire
    if (shell->exec == NULL) {
        perror("Failed to allocate memory for shell->exec");
        exit(EXIT_FAILURE);
    }
    shell->error = NULL;  // Assurez-vous de l'initialiser correctement si nécessaire
    write_inputrc();
}