#include "minishell.h"

char *ft_getenv_var_value(const char *name) 
{
    char *value;
    
    value = getenv(name);
    if (value != NULL) 
        return value;
    else {
        return "";
    }
}

int ft_calculate_new_length(const char *cmd) 
{
    int length = 0;
    int i = 0;
    char *var_name;
    char *var_value;

    while (cmd[i] != '\0') 
    {
        if (cmd[i] == '$') 
        {
            i++;
            int start = i;
            while (cmd[i] != '\0' && cmd[i] != ' ') i++;
            var_name = strndup(cmd + start, i - start);
            var_value = getenv_var_value(var_name);
            length += strlen(var_value);
            free(var_name);
        } else 
        {
            length++;
            i++;
        }
    }
    return length;
}

char *ft_expand_env_variables(const char *cmd, int last_exit_status) 
{
    if (!cmd) return NULL;

    char *result = malloc(calculate_new_length(cmd, last_exit_status) + 1);
    if (!result) return NULL;

    int i = 0, j = 0;
    while (cmd[i] != '\0') {
        if (cmd[i] == '$') {
            char *var_value;
            if (cmd[i + 1] == '?') {
                var_value = ft_itoa(last_exit_status);
                i += 2;
            } else {
                int start = i + 1;
                while (cmd[i] != '\0' && cmd[i] != ' ') i++;
                var_value = getenv_var_value(strndup(cmd + start, i - start));
            }
            strcpy(result + j, var_value);
            j += strlen(var_value);
            free(var_value);
        } else {
            result[j] = cmd[i];
            j++;
            i++;
        }
    }
    result[j] = '\0';
    return result;
}
