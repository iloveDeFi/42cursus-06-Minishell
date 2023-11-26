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

char *ft_strpbrk(const char *s1, const char *s2)
{
    int i = 0;

    while (s1[i] != '\0')
    {
        int j = 0;
        while (s2[j] != '\0')
        {
            if (s1[i] == s2[j])
                return (char *)(s1 + i);
            j++;
        }
        i++;
    }
    return NULL;
}

char *ft_strndup(const char *s, size_t n) 
{
    size_t len;
    size_t i;
    
    len = strlen(s);
    if (len > n) {
        len = n;
    }

    char *new_str = (char *)malloc(len + 1);
    if (new_str == NULL)
        return NULL; 

    i = 0;
    while (i < len)
    {
        new_str[i] = s[i];
        i++;
    }
    new_str[len] = '\0';
    return new_str;
}
