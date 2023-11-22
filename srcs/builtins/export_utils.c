#include "minishell.h" 

int	ft_is_sep(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int ft_only_digit(char *str)
{
    while (*str && ft_isdigit(*str))
        str++;
    if (!*str)
        return (TRUE);
    return (FALSE);
}

/*int	add_var_to_list(t_env **env_list, char *args)
{
	t_env	*new_node;

	new_node = create_node(args);
	if (!new_node)
		return (0);
	if (!is_in_lst(new_node->var, env_list))
		add_to_list(env_list, new_node);
	else
		replace_in_lst(new_node, env_list);
	return (1);
}*/

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
