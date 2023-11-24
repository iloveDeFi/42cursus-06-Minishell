#include "minishell.h"

Commencer a creer les pipes par pair de commande

int pipe1[2]; // Tube entre 1 et 2
int pipe2[2]; // Tube entre 2 et 3

if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
}


commande 1
fork()

all commandes
fork()
pipe(fd)
dup2(fd[x], x)
execvp()

commande last
fork()

int main() {
    int pipe1[2]; // Tube entre 1 et 2
    int pipe2[2]; // Tube entre 2 et 3

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Processus enfant pour la commande 1
    if (fork() == 0) {
        // Rediriger stdout vers pipe1[1]
        // Fermer les descripteurs de fichier inutiles
        // Exécuter la commande 1
    }

    // Processus enfant pour la commande 2
    if (fork() == 0) {
        // Rediriger stdin depuis pipe1[0]
        // Rediriger stdout vers pipe2[1]
        // Fermer les descripteurs de fichier inutiles
        // Exécuter la commande 2
    }

    // Processus enfant pour la commande 3
    if (fork() == 0) {
        // Rediriger stdin depuis pipe2[0]
        // Fermer les descripteurs de fichier inutiles
        // Exécuter la commande 3
    }

    // Fermer les descripteurs de fichier inutiles dans le processus parent

    // Attendre la fin de l'exécution de tous les processus enfants
    // ...

    return 0;
}