#include "minishell.h"

void ft_manage_history(t_mini *shell, const char *input) 
{
    // Vérifier si le fichier d'historique est déjà ouvert
    if (shell->fd_history == -1) 
    {
        shell->fd_history = open("./.history_cmd", O_APPEND | O_WRONLY);
        if (shell->fd_history == -1) 
        {
            perror("Erreur lors de l'ouverture du fichier d'historique");
            return;
        }
    }
    if (input != NULL) 
    {
        // Assurer que la chaîne input est terminée par '\0'
        size_t input_len = strlen(input);
        char *input_copy = malloc(input_len + 1); // +1 pour le caractère nul
        if (input_copy == NULL) 
        {
            perror("Erreur d'allocation de mémoire");
            return;
        }

        strcpy(input_copy, input);

        // Ajouter la commande à l'historique
        add_history(input_copy);

        // Écrire la commande dans le fichier d'historique
        write(shell->fd_history, input_copy, input_len);
        write(shell->fd_history, "\n", 1);

        // Libérer la mémoire allouée pour input_copy
        free(input_copy);
    }
}

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
