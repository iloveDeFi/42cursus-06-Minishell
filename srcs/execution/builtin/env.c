#include "minishell.h"

void	ft_display_envlist(t_env *envList)
{
	t_env	*current;

	current = envList;
	while (current != NULL)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}

int	env(t_env *envList)
{
	ft_display_envlist(envList);
	return (0);
}
