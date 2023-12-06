#include "minishell.h" 

int	ft_is_sep(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	ft_only_digit(char *str)
{
    while (*str && ft_isdigit(*str))
        str++;
    if (!*str)
        return (TRUE);
    return (FALSE);
}

int	add_var_to_list(t_env **envlist, char *args)
{
	t_env	*new_node;

	new_node = create_node(args);
	if (!new_node)
		return (0);
	if (!is_in_lst(new_node->var, envlist))
		add_to_list(envlist, new_node);
	else
		replace_in_lst(new_node, envlist);
	return (1);
}

t_env	*create_node(char *var_array)
{
	t_env	*new_node;
	int		i;

	new_node = malloc(sizeof(t_env));
	i = 0;
	if (new_node)
	{
		while (var_array[i] != '=' && var_array[i] != '\0')
			i++;
		new_node->var = ft_substr(var_array, 0, i);

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


int	is_in_lst(char	*var, t_env **envlist)
{
	t_env	*tmp;
	
	tmp = *envlist;
	if (tmp == NULL || var == NULL)
		return (0);
	while (tmp != NULL && ft_strcmp(tmp->var, var) != 0)
		tmp = tmp->next;
	return (tmp != NULL);
}

void add_to_list(t_env **envlist, t_env *new_node)
{
    if (!envlist || !new_node)
        return;

    new_node->next = *envlist;
    *envlist = new_node;
}

void	replace_in_lst(t_env *new_node, t_env **envlist)
{
	t_env	*tmp;

	tmp = get_in_lst(new_node->var, envlist);
	if (tmp)
		free_node(new_node, tmp, new_node->value);
}

t_env	*get_in_lst(char *var, t_env **envlist)
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

void	free_node(t_env *new_node, t_env *tmp, char *str)
{
	free(tmp->value);
	tmp->value = ft_strdup(str);
	free(new_node->var);
	free(new_node->value);
	free(new_node);
}

void	print_export_list(t_env **envlist)
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

void	delete_list(t_env *envlist)
{
	t_env	*tmp;
	t_env	*node;

	tmp = envlist;
	if (envlist == NULL)
		return ;
	while (tmp != NULL)
	{
		free(tmp->var);
		free(tmp->value);
		node = tmp->next;
		free(tmp);
		tmp = node;
	}
}

t_env	*sort_list_export(t_env **envlist)
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

int	count_list(t_env **list)
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

void	swap_nodes(t_env *tmp)
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

t_env	*ft_envlist_duplicate(t_env **envlist)
{
	t_env	*list;
	t_env	*new;
	t_env	*copy;

	list = *envlist;
	copy = NULL;
	if (*envlist == NULL)
		return (NULL);
	while (list != NULL)
	{
		new = dup_node(list->var, list->value);
		if (copy == NULL)
			copy = new;
		else
			add_to_list(&copy, new);
		list = list->next;
	}
	return (copy);
}

t_env	*dup_node(char *name, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (new_node)
	{
		new_node->var = ft_strdup(name);
		new_node->value = ft_strdup(value);
		new_node->next = NULL;
		return (new_node);
	}
	return (NULL);
}

char **ft_env_duplicate(char **envp)
{
    char **copy;
    int i = 0;

    while (envp[i])
        i++;
    copy = (char **)malloc(sizeof(char *) * (i + 1));
    if (!copy)
        return NULL;
    i = 0;
    while (envp[i])
    {
        copy[i] = ft_strdup(envp[i]);
        if (!copy[i])
        {
            while (i > 0)
            {
                free(copy[i - 1]);
                i--;
            }
            free(copy);
            return NULL;
        }
        i++;
    }
    copy[i] = NULL;
    return copy;
}