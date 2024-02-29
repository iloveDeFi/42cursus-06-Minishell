#include "minishell.h"

void	ft_free_redirection_info(t_redirection_info *redirection_info) 
{
    free(redirection_info->filename);
    free(redirection_info->delimiter);
}
