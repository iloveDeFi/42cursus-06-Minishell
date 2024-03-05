#include "minishell.h"

int	ft_is_alpha(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') \
		|| (c >= '0' && c <= '9') || c == '=')
	{
		return (1);
	}
	return (0);
}

int	ft_check_variable_definition(char *arg)
{
	printf("ft_check_variable_definition\n");
    char	*equals;
	char	*found;
	int		count;

	count = 0;
	found = arg;
	equals = ft_strchr(arg, '=');
	while (*found)
	{
		if (*found == '=')
			count++;
		if (count > 1)
		{
			perror("Invalid variable definition. Use only one equal sign\n");
			exit(EXIT_FAILURE); // ! TODO should not exit the minishell
		}
		found++;
	}
	if (equals == NULL || equals == arg || *equals == '\0')
	{
		printf("equals = %s\n", equals);
        perror("Invalid variable definition. Use VARIABLE=value format.\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	ft_check_export_args(t_command *command)
{
	printf("ft_check_export_args\n");
    char	*arg;
	int		i;

	if (command->argCount > 2)
	{
		perror("Hey, export takes only one argument!\n");
		exit(EXIT_FAILURE); // ! TODO should not exit the minishell
	}
	arg = command->args[1];
	if ((!ft_is_alpha(arg[0])) && arg[0] != '_')
	{
		perror("Export variable must start by a letter or _ \n");
		exit(EXIT_FAILURE); // ! TODO should not exit the minishell
	}
	i = 1;
	while (arg[i] != '\0')
	{
		if (!ft_is_alpha(arg[i]) && arg[i] != '_')
			exit(EXIT_FAILURE); // ! TODO should not exit the minishell
		i++;
	}
	return (0);
}

void	ft_print_exported_vars(t_env *envList)
{
	t_env	*current;

	current = envList;
	while (current != NULL)
	{
		printf("declare -x %s=%s\n", current->name, current->value);
		current = current->next;
	}
}

int	ft_export(t_env **envList, t_command *cmd)
{
	t_env	*current;
	t_env	*newvar;
	char	*name;
	char	*value;

	if (ft_strcmp(cmd->name, "export") == 0 && cmd->args[1] == NULL)
	{
		ft_print_exported_vars(*envList);
		return (0);
	}
	ft_check_variable_definition(cmd->args[1]);
	ft_check_export_args(cmd);
	ft_split_string_export_argument(cmd->args[1], &name, &value);
	newvar = ft_create_node_for_export_argument(name, value);
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
	ft_add_to_list(envList, newvar);
	return (0);
}
