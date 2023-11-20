#include "minishell.h"

char *find_variable_end(const char *str) 
{
    return ft_strpbrk(str, " $");
}

void copy_env_value(char **result, int *j, const char *name) 
{
    char *value = getenv(name);
    int k = 0;
    while (value && value[k] != '\0') {
        (*result)[(*j)++] = value[k++];
    }
}

// TO DO MANAGE MEMORY SIZE FOR EXPANSION
char *expand_single_variable(const char *str, int last_exit_status) {
    char *result = malloc(ft_strlen(str) * 2 + 1); // enough ??
    if (result == NULL) return NULL;
    int i = 0, j = 0;
    char *end, *name, *exit_status_str;
    while (str[i] != '\0') {
        if (str[i] == '$') {
            if (str[i + 1] == '?') {
                exit_status_str = ft_itoa(last_exit_status);
                ft_strcpy(result + j, exit_status_str);
                j += ft_strlen(exit_status_str);
                free(exit_status_str);
                i += 2;
            } else {
                end = find_variable_end(str + i + 1);
                name = ft_strndup(str + i + 1, end - (str + i + 1));
                copy_env_value(&result, &j, name);
                free(name);
                i += (end - (str + i));
            }
        } else
            result[j++] = str[i++];
    }
    result[j] = '\0';
    return result;
}
