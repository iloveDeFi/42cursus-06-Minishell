#include "minishell.h"

void    ft_env(t_envlist *env_list)
{
    t_env *temp = env_list->head;

    while(temp != NULL)
    {
        if (temp->var != NULL)
        {
            ft_putstr_fd(tmp->var, 1);
            write(1, "=", 1);
            ft_putstr_fd(tmp->value, 1);
            write(1, "\n", 1);
        }
        tmp = tmp->next; // Passer à l'élément suivant de la liste
    }
}