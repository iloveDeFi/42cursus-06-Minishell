#include "minishell.h"

int main(int ac, char **av) {

    //signal(SIGINT, handle_signal);
    
    if (ac > 1) 
    {
        fprintf(stderr, "CHAOS, there are too many arguments\n");
        return 1; // Utilisation de 1 pour indiquer une erreur
    }

    while (1) {
        char *input = readline("Minis_Hell> ");

        if (input == NULL) 
        {
            fprintf(stderr, "Exiting...\n");
            break; // Sortir de la boucle si l'utilisateur a saisi Ctrl+D
        }

        add_history(input);

        char *token = ft_strtok(input, " \n");
        int i = 0;
        while (token != NULL) 
        {
            av[i] = token;
            token = ft_strtok(NULL, " \n");
            i++;
        }
        av[i] = NULL; // La dernière entrée doit être NULL pour indiquer la fin des arguments

        // Créer nouveau processus
        pid_t pid = fork();

        if (pid == -1) 
        {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Dans le processus fils, exécutez la commande
            execvp(av[0], av);
            // Si execvp retourne, il y a eu une erreur
            perror("minishell");
            exit(EXIT_FAILURE);
        } else 
        {
            // Dans le processus parent, attendez que le fils se termine
            wait(NULL);
        }
        free(input);
    }
    return 0;
}
