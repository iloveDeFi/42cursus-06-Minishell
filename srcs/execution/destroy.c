#include "minishell.h"

void ft_destroy_commands(t_commandList *commands) 
{
    while (commands != NULL) 
	{
        t_command *next_command = commands->head;
        
        // Libérez la mémoire allouée pour cet élément de la liste de commandes
        free(commands->head->name);
        free(commands->head->redirectFile);
        // Libérez la mémoire allouée pour les arguments de la commande
        if (commands->head->args != NULL) {
            for (int i = 0; commands->head->args[i] != NULL; i++) {
                free(commands->head->args[i]);
            }
            free(commands->head->args);
        }
        
        // Libérez la mémoire de la structure t_command
        free(commands->head);
        
        // Passez à la commande suivante
        free(commands->head);
        commands->head = next_command;
    }
    
    // Libérez la mémoire de la structure t_commandList elle-même
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
