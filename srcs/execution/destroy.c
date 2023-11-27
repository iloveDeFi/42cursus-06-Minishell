#include "minishell.h"

void destroy_commands(t_commandList *commands) 
{
    while (commands != NULL) 
	{
        t_command *next_command = commands->head;
        
        // Libérez la mémoire allouée pour cet élément de la liste de commandes
        free(commands->head->name);
        free(commands->head->redirectFile);
        // Libérez la mémoire allouée pour les arguments de la commande
        if (commands->head->arguments != NULL) {
            for (int i = 0; commands->head->arguments[i] != NULL; i++) {
                free(commands->head->arguments[i]);
            }
            free(commands->head->arguments);
        }
        // Passez à la commande suivante
        free(commands->head);
        commands->head = next_command;
    }
    free(commands);
}

void ft_destroy_current_shell(t_mini *mini)
{
    // Détruisez les commandes en appelant la fonction destroy_commands
    destroy_commands(mini->exec->commands);
    
    if (mini->av != NULL)
    {
        free(mini->av);
        mini->av = NULL;
    }
    
    // Vous devez également détruire d'autres membres de la structure mini
    // si nécessaire, en fonction de leur type et de leur gestion de la mémoire.
    
    if (mini->error != NULL)
        free(mini->error);
    
    if (mini->exec != NULL)
    {
        free(mini->exec);
        mini->exec = NULL;
    }
}
