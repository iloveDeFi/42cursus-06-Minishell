#include "minishell.h"

// void destroy_commands(t_command *commands) 
// {
//     if (commands == NULL)
//         return ;
    
//     while (commands != NULL) 
//     {
//         t_command *next_command = commands;
        
//         // Libérez la mémoire allouée pour cet élément de la liste de commandes
//         free(commands->name);
//         free(commands->redirectFile);
//         // Libérez la mémoire allouée pour les arguments de la commande
//         if (commands->args != NULL) {
//             for (int i = 0; commands->args[i] != NULL; i++) {
//                 free(commands->args[i]);
//             }
//             free(commands->args);
//         }
//         // Passez à la commande suivante
//         free(commands);
//         commands = next_command;
//     }
//     free(commands);
// }

void ft_destroy_current_shell(t_mini *mini)
{
    // Détruisez les commandes en appelant la fonction destroy_commands
    if (mini->commands != NULL) 
    {
        destroy_commands(mini->commands);
        free(mini->commands);
        mini->commands = NULL;
    }
    if (mini->av != NULL)
    {
        free(mini->av);
        mini->av = NULL;
    }   
    if (mini->error != NULL) 
    {
        free(mini->error);
        mini->error = NULL;
    }
    
    if (mini->exec != NULL)
    {
        free(mini->exec);
        mini->exec = NULL;
    }
}