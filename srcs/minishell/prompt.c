#include "minishell.h"

void ft_custom_prompt_msg(t_mini *shell) {
    if (shell->av != NULL) {
        free(shell->av);
        shell->av = NULL; // Assurez-vous de mettre à NULL après la libération
    }

    char *input = readline("\033[32mminishell$ \033[0m");

    // Vérifiez si l'utilisateur a appuyé sur Ctrl+D pour éviter de copier une chaîne NULL
    if (input != NULL) {
        shell->av = ft_strdup(input);
        free(input); // Libérez la mémoire allouée par readline après la copie
    }
}
