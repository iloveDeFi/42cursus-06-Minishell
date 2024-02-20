#include "minishell.h"

void	ft_display_envlist(t_env *envlist)
{
	t_env	*current;

	current = envlist;
	while (current != NULL)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}

int	env(t_env *envlist)
{
	ft_display_envlist(envlist);
	return (0);
}
