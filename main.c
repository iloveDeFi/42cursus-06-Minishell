

#include "minishell.h"

// TO DO : gestion des quotes, caractères spéciaux etc

int main(int ac, char **av, char **env)
{
    if (ac > 1)
        return (str_error("CHAOS, there are too many arguments", 0));
    while (1)
    {
        printf("Minis_Hell> ");
        fgets(input, sizeof(input), stdin); // lire l'entrée utilisateur
        char *token = strtok(input, " \n");
        int i = 0;
        while(toekn != NULL) {
            args[i] = token;
            token = strtok(NULL, " \n");
            i++;
        }
        args[i] = NULL; // La dernière entrée doit être NULL pour indiquer la fin des arguments

        // Créer un nouveau processus
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Dans le processus fils, exécutez la commande
            execvp(args[0], args);
            // Si execvp retourne, il y a eu une erreur
            perror("minishell");
            exit(EXIT_FAILURE);
        } else {
            // Dans le processus parent, attendez que le fils se termine
            wait(NULL);
        }
    }
}
