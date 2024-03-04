#include "minishell.h"

void	ft_free_split(char **arr)
{
	int i;
	
	if (arr == NULL)
        return;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char *ft_strstr(const char *haystack, const char *needle) 
{
    const char *h;
    const char *n;

    if (*needle == '\0') {
        return (char *)haystack;
    }

    while (*haystack != '\0') {
        h = haystack;
        n = needle;

        while (*h != '\0' && *n != '\0' && *h == *n) {
            h++;
            n++;
        }

        if (*n == '\0') {
            return (char *)haystack;
        }

        haystack++;
    }

    return NULL;
}
