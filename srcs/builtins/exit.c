/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienbelda <julienbelda@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 01:12:14 by bat               #+#    #+#             */
/*   Updated: 2023/11/15 10:12:26 by julienbelda      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction pour gérer la commande "exit"
/*void exit(t_command *command) 
{
    int exit_code;
    
    exit_code = ft_atoi(command->arguments[1]);
    if (command->arguments[1] != NULL) 
    {   
        if (exit_code == 0) 
            exit(exit_code);
        else 
        {
            printf(stderr, "Invalid exit code: %s\n", command->arguments[1]);
            exit(EXIT_FAILURE);
        }
    } 
    else 
        exit(0);
}*/
