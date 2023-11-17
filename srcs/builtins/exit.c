/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienbelda <julienbelda@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 01:12:14 by bat               #+#    #+#             */
/*   Updated: 2023/11/16 13:36:37 by julienbelda      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction pour gérer la commande "exit"
void ft_exit(t_command *command) 
{
    int exit_code;
    
    if (command->arguments[1] != NULL) 
    {   
        exit_code = ft_atoi(command->arguments[1]);
        if (exit_code == 0) 
            exit(exit_code);
        else 
        {
            // Rediriger stderr vers stdout
            if (dup2(STDOUT_FILENO, STDERR_FILENO) == -1) {
                perror("dup2");
                exit(EXIT_FAILURE);
            }

            printf("Invalid exit code: %s\n", command->arguments[1]);
            exit(EXIT_FAILURE);
        }
    } 
    else 
        exit(0);
}

