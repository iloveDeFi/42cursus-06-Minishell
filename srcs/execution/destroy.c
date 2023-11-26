#include "minishell.h"

void destroy_children(t_mini *mini) 
{
    t_global *child = mini->child;
    while (child != NULL) {
        t_global *next_child = child->next;
        // Libérez les ressources associées à child ici, si nécessaire
        free(child);
        child = next_child;
    }
    mini->child = NULL; // Mettez à jour le pointeur child pour indiquer que la liste est vide
}

void ft_destroy_current_shell(t_mini *mini)
{
	destroy_children(mini);
	if (mini->av)
	{
		free(mini->av);
		mini->av = NULL;
	}
	mini->av = NULL;
	if (mini->error)
		free(mini->error);
	if (mini->exec)
	{
		free(mini->exec);
		mini->exec = NULL;
	}
}