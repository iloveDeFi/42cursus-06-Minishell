/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienbelda <julienbelda@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:45:10 by bat               #+#    #+#             */
/*   Updated: 2023/11/28 20:18:23 by julienbelda      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void ft_execute_external_command(t_command *cmd) 
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid == 0) 
    { 
        // Dans le processus enfant
        if (execve(cmd) == -1) 
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
*/