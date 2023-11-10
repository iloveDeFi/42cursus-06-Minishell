#include "minishell.h"

void ft_redirect_output(t_command *command, char *input)
{
    int i;

    i = 0;
    while(input[++i] != '\0')
    {
        if (input[i] == 62 && input[i + 1] != 62)
        {

        }
        else if (input[i] == 62 && input[i + 1] == 62)
        {

        }
    }
    return NULL;
}
