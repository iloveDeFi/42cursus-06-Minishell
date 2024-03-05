#include "minishell.h"

void	ft_free_redirection_info(t_redirection_info *redirection_info) 
{
	(void)redirection_info;
	//
	write(1, "enter in ft_free_redirection_info\n", 34);
    // free(redirection_info->filename);
    // free(redirection_info->delimiter);
}
