/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienbelda <julienbelda@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:45:10 by bat               #+#    #+#             */
/*   Updated: 2023/12/01 14:47:38 by julienbelda      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_execute_external_command(char *cmdPath, char *args[]) 
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid == 0) 
    { 
        // Dans le processus enfant
        if (execve(cmdPath, args, NULL) == -1) 
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
    {
        // Dans le processus parent
        waitpid(pid, &status, 0);

        if (WIFEXITED(status))
        {
            int exitStatus = WEXITSTATUS(status);
            printf("Le processus enfant s'est terminé avec le code de sortie : %d\n", exitStatus);
        }
        else if (WIFSIGNALED(status))
        {
            int signalNumber = WTERMSIG(status);
            printf("Le processus enfant a été interrompu par le signal : %d\n", signalNumber);
        }
    }
}
