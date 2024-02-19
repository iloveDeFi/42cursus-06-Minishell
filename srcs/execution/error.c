#include "minishell.h"

int ft_is_only_spaces(const char *str)
{
    while (*str)
    {
        if (*str != ' ')
        {
            return 1;
        }
        str++;
    }
    return 0;
}

void ft_handle_only_spaces(t_mini *shell)
{
    if (ft_is_only_spaces(shell->av))
    {
        ft_destroy_current_shell(shell);
        return;
    }
}

void ft_check_null_av_shell(t_mini *shell)
{
	if (shell->av == NULL) 
    {
        perror("av == NULL\n");
		exit(EXIT_FAILURE);
    }
}

void ft_check_empty_av_shell(t_mini *shell)
{
	if ((ft_strcmp(shell->av, "") == 0))
	{
		perror("Hey, the shell argv is an empty string\n");
		exit(EXIT_FAILURE);
	}
}

int ft_check_if_input_is_tokenizable(t_commandList *commandList, char *input) 
{	
	
    if (commandList == NULL)
    {
        perror("Hey commandList head is NULL, so input is not tokenizable\n");
        return 1;
    }
    else if (ft_tokenize_input_with_strtok(commandList, input))
    {
        return 0;
    } 
    else 
    {
        perror("Parsing failed in ft_check_if_input_is_tokenizable");
        ft_destroy_commandList(commandList);
        return 1;
    }
}
