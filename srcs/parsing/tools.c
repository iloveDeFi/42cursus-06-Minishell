#include "minishell.h"

int ft_check_pipe_or_redir(char c)
{
    if (c == '>' || c == '<' || c == '|')
        return (1);
    return (0);
}

int	ft_check_white_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\r'
        || c == '\n' || c == '\v' || c == '\f')
        return (1);
    return (0);
}

int ft_check_quote(char c) 
{
    if (c == '\'' || c == '"')
        return (1);
    return (0);
}

int ft_check_quotes_error(void)
{
    write (1, "Chaos, quote(s) problem", 24);
    return (1);
}