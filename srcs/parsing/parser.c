/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:44:27 by bat               #+#    #+#             */
/*   Updated: 2023/11/03 16:39:51 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int split_arg(t_argList *argList, char *input)
{
    char *token;
    
    token = ft_strtok(input, " ");
    while (token != NULL)
    {
        t_arg *newArg = malloc(sizeof(t_arg));
        if (newArg == NULL)
        {
            perror("CHAOS, error allocating memory");
            exit(EXIT_FAILURE);
        }
        newArg->name = ft_strdup(token);
        if (argList->head == NULL)
        {
            argList->head = newArg;
            argList->tail = newArg;
            newArg->prev = NULL; 
        }
        else {
            newArg->prev = argList->tail;
            //argList->tail->next = newArg;
            argList->tail = newArg;
        }
        argList->arglistLength++;
        token = strtok(NULL, " ");
    }
    return argList->arglistLength;
}