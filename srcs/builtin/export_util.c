#include "minishell.h" 

int	ft_is_sep(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	ft_is_only_digit(char *str)
{
    while (*str && ft_isdigit(*str))
        str++;
    if (!*str)
        return (TRUE);
    return (FALSE);
}

int	ft_add_envVar_to_list(char *name, t_env **envlist)
{
	t_env	*new_node;

	new_node = ft_create_node_envVar(new_node->var);
	if (!new_node)
		return (0);
	if (!ft_is_in_list(new_node->var, envlist))
		ft_add_to_list(envlist, new_node);
	else
		replace_in_list(new_node, envlist);
	return (1);
}

void ft_print_export_list(t_env **envlist)
{
	t_env	*tmp;
	t_env	*sort_list;

	sort_list = sort_list_export(envlist);
	tmp = sort_list;
	while (tmp != NULL)
	{
		if (tmp->var != NULL)
		{
			ft_putstr_fd(tmp->var, 1);
			write(1, "=", 1);
			ft_putstr_fd(tmp->value, 1);
		}
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	delete_list(sort_list);
}



t_env	*ft_sort_list_export(t_env **envlist)
{
	t_env	*tmp;
	t_env	*sort_list;
	int		i;

	sort_list = ft_envlist_duplicate(envlist);
	i = count_list(&sort_list);
	tmp = sort_list;
	while (i > 0)
	{
		tmp = sort_list;
		while (tmp->next != NULL)
		{
			swap_nodes(tmp);
			tmp = tmp->next;
		}
		i--;
	}
	return (sort_list);
}

int	ft_count_list(t_env **list)
{
	int		i;
	t_env	*tmp;

	tmp = *list;
	i = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	ft_swap_nodes(t_env *tmp)
{
	char	*name;
	char	*value;

	if (ft_strcmp(tmp->var, tmp->next->var) > 0)
	{
		name = ft_strdup(tmp->next->var);
		value = ft_strdup(tmp->next->value);
		free(tmp->next->var);
		free(tmp->next->value);
		tmp->next->var = ft_strdup(tmp->var);
		tmp->next->value = ft_strdup(tmp->value);
		free(tmp->var);
		free(tmp->value);
		tmp->var = ft_strdup(name);
		tmp->value = ft_strdup(value);
		free(name);
		free(value);
	}
}

t_env	*ft_get_in_list(char *var, t_env **envlist)
{
	t_env	*tmp;

	tmp = *envlist;
	if (tmp == NULL || var == NULL)
		return (NULL);
	while (tmp != NULL && ft_strcmp(tmp->var, var) != 0)
		tmp = tmp->next;
	if (tmp)
		return (tmp);
	return (NULL);
}