
#include "minishell.h"

int echo(t_command **args) {
    const char *message = "An error occurred: not enough arguments\n";

    // Vérifier si le tableau d'arguments est vide
    if (args == NULL || args[0] == NULL || args[0]->args == NULL) {
        write(STDERR_FILENO, message, strlen(message));
        return 1;  // ou un autre code d'erreur selon votre convention
    }

    // Afficher les arguments
    int i = 0;
    while (args[0]->args[i] != NULL) {
        write(STDOUT_FILENO, args[0]->args[i], strlen(args[0]->args[i]));
        if (args[0]->args[i + 1] != NULL)
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    write(STDOUT_FILENO, "\n", 1);

    return 0;  // ou un autre code de réussite selon votre convention
}



