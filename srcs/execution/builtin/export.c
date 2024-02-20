#include "minishell.h"

int ft_is_alpha(char c) 
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '=')
	{
		return (1);
	}
	return (0);
}

int ft_check_variable_definition(char *arg)
{
    char *equals;
    char *found;
    int count;
    
    count = 0;
    found = arg;
    equals = ft_strchr(arg, '=');
    while(*found)
    {
        if (*found == '=')
            count++;
        if (count > 1)
        {
            perror("Invalid variable definition. Use only one equal sign\n");
            exit(EXIT_FAILURE);
        }
        found++;
    }

    if (equals == NULL || equals == arg || *equals == '\0') 
    {
        perror("Invalid variable definition. Use VARIABLE=value format.\n");
        exit(EXIT_FAILURE);
    }
    return (0);
}

int ft_check_export_args(t_command *command)
{
	char *arg;
	int i;

	if (command->argCount > 2) 
	{
		perror("Hey, export takes only one argument!\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	arg = command->args[1];
	printf("command->args[0] value is: %s\n", command->args[0]);
	printf("command->args[1] value is: %s\n", arg);
	printf("ARG[0] value is: %c\n", arg[0]);
	printf("ARG[1] value is: %c\n", arg[1]);

	// Ajoutez ces lignes de débogage
	printf("Checking first character: %c\n", arg[0]);

	if ((!ft_is_alpha(arg[0])) && arg[0] != '_') 
	{
		perror("Export variable must start by a letter or _ \n");
		exit(EXIT_FAILURE);
	}

	// Ajoutez ces lignes de débogage
	printf("Before checking other characters\n");

	i = 1;
	while (arg[i] != '\0') 
	{
		if (!ft_is_alpha(arg[i]) && arg[i] != '_') 
		{
			printf("Invalid character found: %c\n", arg[i]);
			perror("Export variable must contain only letters, numbers, or _ \n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return 0;
}

void ft_print_exported_vars(t_env *envList) 
{
    t_env *current;
    
    current = envList;
    while (current != NULL) 
    {
        printf("%s=%s\n", current->name, current->value);
        current = current->next;
    }
}

int ft_export(t_env **envList, t_command *cmd)
{
	t_env *current;
	t_env *newVar;
	char *name;
	char *value;

	if (ft_strcmp(cmd->name, "export") == 0 && cmd->argCount == 1)
	{
		ft_print_exported_vars(*envList);
		return (0);
	}
	ft_check_variable_definition(cmd->args[1]);
	ft_check_export_args(cmd);
	ft_split_string_export_argument(cmd->args[1], &name, &value);
	newVar = ft_create_node_for_export_argument(name, value);
	current = *envList;
	while (current != NULL)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return (0);
		}
		current = current->next;
	}
	ft_add_to_list(envList, newVar);
	return (0);
}

