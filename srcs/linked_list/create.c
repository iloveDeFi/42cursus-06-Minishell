#include "minishell.h"

t_env	*ft_create_node_for_envList(char *var_array)
{
	t_env	*new_node;
	int		i;

	i = 0;
	new_node = malloc(sizeof(t_env));
	if (new_node)
	{
		while (var_array[i] != '=' && var_array[i] != '\0')
			i++;
		new_node->name = ft_substr(var_array, 0, i);

		if (var_array[i] == '\0')
		{
			// Cas où var_array ne contient pas le caractère '='
			new_node->value = ft_strdup("");
		}
		else
		{
			i++; // Ignorer le caractère '='
			new_node->value = ft_strdup(var_array + i);
		}

		new_node->next = NULL;
		return new_node;
	}
	return NULL;
}

t_command *ft_create_and_init_new_command_in_commandList(t_commandList *commandList, char *name) 
{
    t_command *command = (t_command *)malloc(sizeof(t_command));

    if (command == NULL) 
    {
        perror("CHAOS, error allocating memory");
        ft_destroy_command(commandList);
        exit(EXIT_FAILURE);
    }
    ft_init_new_node(commandList, command, name);
    return command;
}

void ft_init_new_node(t_commandList *commandList, t_command *command, char *token)
{
    command->name = ft_strdup(token);
    command->data = NULL;
    command->args = (char **)malloc(sizeof(char *) * 2);
    if (command->args == NULL) 
    {
        perror("CHAOS, error allocating memory");
        ft_destroy_command(commandList);
        exit(EXIT_FAILURE);
    }
    command->args[0] = ft_strdup(token);
    command->args[1] = NULL;
    command->argCount = 1;
    command->redirectFile = NULL;
    command->next = NULL;
    command->prev = NULL;
    command->tokenType = ft_allocate_token_type(token);
    command->quoteType = ft_check_and_allocate_quote_type(token);
	command->envp = NULL;  // Vous pouvez initialiser envp avec les valeurs appropriées si nécessaire
    command->commands = NULL;  // Initialiser à NULL car cela dépendra du contexte d'utilisation
    command->envList = NULL;  // Initialiser à NULL si vous n'avez pas d'environnement spécifique à ce stade
    ft_memset(command->pipes, 0, sizeof(command->pipes));  // Initialiser la matrice pipes avec zéros
    ft_memset(command->child_pids, 0, sizeof(command->child_pids));  // Initialiser le tableau child_pids avec zéros
    command->pipe_index = 0;
}

t_env *ft_create_node_for_export_argument(char *name, char *value)
{
    t_env *new_node;
    
    new_node = malloc(sizeof(t_env));
    if (new_node == NULL) 
    {
        perror("Memory allocation error in ft_create_node_export_argument\n");
        exit(EXIT_FAILURE);
    }

    new_node->name = ft_strdup(name);
    new_node->value = ft_strdup(value);
    new_node->next = NULL;
    
    return new_node;
}
