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
	i = ft_count_list(&sort_list);
	tmp = sort_list;
	while (i > 0)
	{
		tmp = sort_list;
		while (tmp->next != NULL)
		{
			ft_swap_nodes(tmp);
			tmp = tmp->next;
		}
		i--;
	}
	return (sort_list);
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
			ft_swap_nodes(tmp);
			tmp = tmp->next;
		}
		i--;
	}
	return (sort_list);
}
