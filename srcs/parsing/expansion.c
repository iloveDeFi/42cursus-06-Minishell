#include "minishell.h"

char *ft_getenv_var_value(const char *name) {
    char *value;
    
    value = getenv(name);
    if (value != NULL) {
        return value;
    } else {
        return "";
    }
}

int ft_calculate_new_length(const char *cmd, int last_exit_status) {
    int length = 0;
    int i = 0;

    while (cmd[i] != '\0') {
        if (cmd[i] == '$') {
            i++;
            if (cmd[i] == '?') {
                char *status_str = ft_itoa(last_exit_status);
                length += ft_strlen(status_str);
                free(status_str);
                i++;
            } else {
                int start = i;
                while (cmd[i] != '\0' && cmd[i] != ' ') i++;
                char *var_name = ft_strndup(cmd + start, i - start);
                char *var_value = ft_getenv_var_value(var_name);
                length += ft_strlen(var_value);
                // free(var_name); ne pas libérer car cela pourrait 
                //essayer de libérer une chaîne littérale ou un pointeur 
                // interne de getenv, ce qui n'est pas valide et peut 
                //conduire à un comportement indéfini.
            }
        } else {
            length++;
            i++;
        }
    }
    return length;
}

char *ft_expand_env_variables(const char *cmd, int last_exit_status) 
{
    if (!cmd) return NULL;

    char *result = malloc(ft_calculate_new_length(cmd, last_exit_status) + 1);
    if (!result) return NULL;

    int i = 0, j = 0;
    while (cmd[i] != '\0') {
        if (cmd[i] == '$') {
            i++;
            char *var_value;
            if (cmd[i] == '?') {
                var_value = ft_itoa(last_exit_status);
                i++;
            } else {
                int start = i;
                while (cmd[i] != '\0' && cmd[i] != ' ') i++;
                char *var_name = ft_strndup(cmd + start, i - start);
                var_value = ft_getenv_var_value(var_name);
                // free(var_name); ne pas libérer car cela pourrait 
                //essayer de libérer une chaîne littérale ou un pointeur 
                // interne de getenv, ce qui n'est pas valide et peut 
                //conduire à un comportement indéfini.
            }
            ft_strcpy(result + j, var_value);
            j += ft_strlen(var_value);
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
