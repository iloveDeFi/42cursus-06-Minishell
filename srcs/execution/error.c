#include "minishell.h"

bool ft_is_only_spaces(const char *str)
{
    while (*str)
    {
        if (*str != ' ')
        {
            return false;
        }
        str++;
    }
    return true;
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
    if (shell->av == NULL || shell->av[0] == '\0')
    {
        perror("Hey, the shell argv is an empty string or a null pointer\n");
        exit(EXIT_FAILURE);
    }
}

int ft_check_if_input_is_tokenizable(t_commandList *commandList, char *input)
{
	int tokenCount;

    if (commandList == NULL)
    {
        perror("Error: commandList is NULL in ft_check_if_input_is_tokenizable\n");
        return 1;
    }
	tokenCount = ft_tokenize_input_with_strtok(commandList, input);
	if (tokenCount > 0)
    {
        return 0; // Input is tokenizable
    }
    else
    {
        perror("Error: Parsing failed in ft_check_if_input_is_tokenizable\n");
        ft_destroy_commandList(commandList);
        return 1; // Parsing failed
    }
}

