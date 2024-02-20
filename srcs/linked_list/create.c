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
    printf("enter create init new command\n");
    t_command *command = (t_command *)malloc(sizeof(t_command));

    if (command == NULL) 
    {
        perror("CHAOS, error allocating memory");
        ft_destroy_commandList(commandList);
        exit(EXIT_FAILURE);
    }
    ft_init_new_node(commandList, command, name);
    printf("init new node\n");
	ft_print_commandList(commandList);
    return command;
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
