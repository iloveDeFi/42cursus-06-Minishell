#include "minishell.h"

void	ft_manage_history(t_mini *shell, const char *input)
{
    // Vérifier si le fichier d'historique est déjà ouvert
    if (shell->fd_history == -1) {
        shell->fd_history = open("./.history_cmd", O_APPEND | O_WRONLY);
        if (shell->fd_history == -1) {
            perror("Erreur lors de l'ouverture du fichier d'historique");
            return;
        }
    }

    // Ajouter la commande à l'historique (assurez-vous que cette fonction est correctement définie)
    add_history(input);

    // Copier la valeur de input dans shell->av
    //if (shell->av != NULL) {
     //  free(shell->av);
    //}
    shell->av = ft_strdup(input);

    // Écrire la commande dans le fichier d'historique
    write(shell->fd_history, input, ft_strlen(input));
    write(shell->fd_history, "\n", 1);

    // Fermer le fichier d'historique (vous devez le fermer après avoir écrit les données)
    close(shell->fd_history);
    
    // Initialisation des erreurs (si nécessaire)
    // initialization_of_errors(shell);
}
