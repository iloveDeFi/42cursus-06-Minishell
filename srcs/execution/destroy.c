#include "minishell.h"

void ft_destroy_commands(t_command *commands) 
{
    if (commands == NULL)
        return;

    while (commands != NULL) 
    {
        t_command *next_command = commands->next;

        // Libérez la mémoire allouée pour cet élément de la liste de commandes
        free(commands->name);
        free(commands->redirectFile);

        // Libérez la mémoire allouée pour les arguments de la commande
        if (commands->args != NULL) {
            int i = 0;
            while (commands->args[i] != NULL) {
                free(commands->args[i]);
                i++;
            }
            free(commands->args);
        }

        // Libérez la mémoire de la structure t_command
        free(commands);

        // Passez à la commande suivante
        commands = next_command;
    }
}



void ft_destroy_current_shell(t_mini *mini)
{
    // Détruisez les commandes en appelant la fonction destroy_commands
    if (mini->commands != NULL) {
        ft_destroy_commands(mini->commands);
        free(mini->commands);
        mini->commands = NULL;
    }
    
    if (mini->av != NULL)
    {
        free(mini->av);
        mini->av = NULL;
    }
    
    // Vous devez également détruire d'autres membres de la structure mini
    // si nécessaire, en fonction de leur type et de leur gestion de la mémoire.
    
    if (mini->error != NULL) {
        free(mini->error);
        mini->error = NULL;
    }
    
    if (mini->exec != NULL)
    {
        free(mini->exec);
        mini->exec = NULL;
    }
}
