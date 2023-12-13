#include "minishell.h"

int echo(t_command *cmd) {
    const char *message = "An error occurred: not enough arguments\n";

    if (cmd->args == NULL || cmd->args[0] == NULL) {
        write(STDERR_FILENO, message, strlen(message));
        return 1;
    }

    int i = 0;
    while (cmd->args[i] != NULL) {
        write(STDOUT_FILENO, cmd->args[i], strlen(cmd->args[i]));
        if (cmd->args[i + 1] != NULL)
            write(STDOUT_FILENO, " ", 1);
        i++;
    }

    // Ajouter une nouvelle ligne à la fin de la sortie
    write(STDOUT_FILENO, "\n", 1);

    return 0;
}



int ft_count_args(char **args) {
    int count = 0;
    while (args[count] != NULL) {
        count++;
    }
    return count;
}


