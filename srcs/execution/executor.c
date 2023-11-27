/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:45:10 by bat               #+#    #+#             */
/*   Updated: 2023/11/27 17:42:37 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_execute_external_command(char *command, char *args[]) 
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid == 0) 
    { 
        // Dans le processus enfant
        if (execve(command, args, NULL) == -1) 
        {
            perror("Erreur lors de l'exécution de la commande");
            exit(EXIT_FAILURE);
        }
    } 
    else if (pid < 0) 
    {
        perror("Erreur lors de la création du processus enfant");
    } 
    else 
    //Dans le processus parents
        wait(&status);
}
