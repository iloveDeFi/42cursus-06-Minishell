#include "minishell.h"

int ft_is_pipe_or_redir(char c)
{
    if (c == '>' || c == '<' || c == '|')
        return (1);
    return (0);
}

int	ft_is_white_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\r'
        || c == '\n' || c == '\v' || c == '\f')
        return (1);
    return (0);
}