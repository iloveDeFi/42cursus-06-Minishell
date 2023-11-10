#include "minishell.h"

char *ft_strtrim_with_quotes(char *str)
{
    int len;
    int start;
    int end;
    int i;
    char *result;

    len = strlen(str);
    start = 0;
    end = len - 1;
    i = 0;
    if (str == NULL)
        return NULL;
    while (str[start] != '\0' && (ft_is_white_space(str[start])))
        start++;
    end = len - 1;
    while (str[end] >= 0 && ft_is_white_space(str[end]))
        end--;
    i = 0;
    result = (char *)malloc(sizeof(char) * (end - start + 2));
    while (start <= end)
    {
        result[i] = str[start]; 
        start++;
        i++;
    }
    result[i] = '\0';
    return (result);
}
