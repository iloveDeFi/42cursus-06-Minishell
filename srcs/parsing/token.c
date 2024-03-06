#include "minishell.h"

char **	ft_tokenize_input_with_strtok(char *input) // TODO rename
{
   return(ft_split(input, ' '));
}

