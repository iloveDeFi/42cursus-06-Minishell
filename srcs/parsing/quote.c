#include "minishell.h"

void	ft_remove_quotes(char *input)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(input);
	while (i < len)
	{
		if (input[i] != '"')
		{
			input[j++] = input[i];
            printf("input[j] = %c\n", input[j]);
		}
        i++;
        printf("i = %d\n", i);
	}
	input[j] = '\0';
}

bool	ft_check_quotes(char *input)
{
	int	single_quotes;
	int	double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	while (*input)
	{
		if (*input == '\'')
			single_quotes++;
		else if (*input == '"')
			double_quotes++;
		input++;
	}
	if (single_quotes % 2 == 0 && double_quotes % 2 == 0)
		return (true);
	else
	{
		g_exit_code = 1;
		return (false);
	}
}

int ft_token_is_a_quotes(char *input)
{
    int i;

    i = 0;
    while (input[i])
    {
        if (input[i] == '"' || input[i] == '\'')
        {
            printf("input[i] = %c\n", input[i]);
            return (true);
        }    
        i++;
    }
    return (false);
}