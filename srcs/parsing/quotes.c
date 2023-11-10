#include "minishell.h"

int ft_is_quote(char c) 
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

void ft_tokenize_with_quotes(char *input)
{
    char *current_char = input;
    char *starting_token = input;

    while (*current_char != '\0')
    {
        if (ft_is_quote(*current_char))
        {
            char quote = *current_char;
            current_char += 1;
            while (*current_char != quote && *current_char != '\0')
                current_char++;
        }
        if (*current_char == '\0')
        {
            fprintf(stderr, "Error: Unterminated quote\n");
            return;
        }
        current_char++;
        else if (*current_char == ' ')
        {
            *current_char = '\0';
            printf("Token : \"%s\"\n", starting_token);
            starting_token = ++current_char;
        }
        else 
            current_char++;
    }
    printf("Token : \"%s\"\n", starting_token);
}
