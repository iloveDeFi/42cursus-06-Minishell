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
    while (str[start] != '\0' && ((ft_is_white_space(str[start])) || ft_is_quote(str[start])))
        start++;
    end = len - 1;
    while (str[end] >= 0 && (ft_is_white_space(str[end]) || ft_is_quote(str[end])))
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


char *ft_strcpy(char *dest, const char *src)
{
    int i = 0;

    if (dest == NULL || src == NULL)
        return NULL;

    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0'; // N'oubliez pas de terminer la chaîne de destination
    return dest;
}
