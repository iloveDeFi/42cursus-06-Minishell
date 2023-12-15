#include "minishell.h"

int echo(t_command *cmd) 
{
    const char *message = "An error occurred: not enough arguments\n";

    if (cmd->args == NULL || cmd->args[0] == NULL) 
    {
        write(STDERR_FILENO, message, strlen(message));
        return 1;
    }

    int i = 0;
    int suppressNewline = 0;  // Ajout de cette variable pour gérer l'option -n

    // Vérifier si la première option est -n
    if (strcmp(cmd->args[0], "-n") == 0) 
    {
        suppressNewline = 1;
        i++;  // Passer à l'argument suivant
    }

    while (cmd->args[i] != NULL) 
    {
        write(STDOUT_FILENO, cmd->args[i], strlen(cmd->args[i]));
        if (cmd->args[i + 1] != NULL)
            write(STDOUT_FILENO, " ", 1);
        i++;
    }

    // Ajouter une nouvelle ligne à la fin de la sortie, sauf si -n est spécifié
    if (!suppressNewline) 
    {
        write(STDOUT_FILENO, "\n", 1);
    }

    return 0;
}
