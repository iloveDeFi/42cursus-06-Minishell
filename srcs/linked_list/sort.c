#include "minishell.h"

t_env	*ft_insert_sorted(t_env *head, t_env *new_node)
{
	if (head == NULL || strcmp(new_node->name, head->name) < 0)
	{
		new_node->next = head;
		return (new_node);
	}
	head->next = ft_insert_sorted(head->next, new_node);
	return (head);
}

// Fonction pour trier la liste récursivement
t_env	*ft_sort_list(t_env *head)
{
	t_env	*sorted_tail;

	if (head == NULL || head->next == NULL)
		return (head);
	sorted_tail = ft_sort_list(head->next);
	head->next = NULL;
	return (ft_insert_sorted(sorted_tail, head));
}

// Fonction pour imprimer les variables exportées dans l'ordre alphabétique
void	ft_print_exported_vars(t_env *env_list)
{
	env_list = ft_sort_list(env_list);
	while (env_list != NULL)
	{
		printf("declare -x %s=%s\n", env_list->name, env_list->value);
		env_list = env_list->next;
	}
}
