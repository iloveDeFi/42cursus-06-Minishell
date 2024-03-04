#include "minishell.h"

void	ft_destroy_current_shell(t_mini *mini)
{
    if (mini->cmd != NULL)
    {
        ft_destroy_commandList(mini->cmd);
    }
    if (mini->av == NULL)
    {
        free(mini->av);
    }
    if (mini->error != NULL)
    {
        free(mini->error);
    }
}
