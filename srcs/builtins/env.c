#include "minishell.h"

int ft_env(t_envList *env_list)
{
    if (env_list == NULL)
        return (EXIT_FAILURE);

    t_node *tmp_node = env_list->head;

    while (tmp_node != NULL)
    {
        t_env *tmp = (t_env *)tmp_node->data;
        if (tmp != NULL && tmp->var != NULL)
        {
            write(1, tmp->var, strlen(tmp->var));
            write(1, "=", 1);
            write(1, tmp->value, strlen(tmp->value));
            write(1, "\n", 1);
        }
        tmp_node = tmp_node->next;
    }
    return (EXIT_SUCCESS);
}
