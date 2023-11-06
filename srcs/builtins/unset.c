/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienbelda <julienbelda@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 01:12:29 by bat               #+#    #+#             */
/*   Updated: 2023/11/06 15:57:56 by julienbelda      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int unset(t_global *global, char *arg) 
{
    int exit_code = 0;
    t_envVar *tmp = global->envVars->head;
    t_envVar *prev = NULL;

    while (tmp) 
    {
        if (strcmp(arg, tmp->name) == 0) 
        {
            if (prev == NULL)
                global->envVars->head = tmp->next;
            else
                prev->next = tmp->next;
            free(tmp->name);
            free(tmp->value);
            free(tmp);
            break;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    if (!is_valid_identifier(arg)) 
        exit_code = EXIT_FAILURE;
    if (exit_code != 0)
        return exit_code;
    return EXIT_SUCCESS;
}


// Helper function to check if a string is a valid identifier
int is_valid_identifier(const char *name)
{
    int i;

    i = 1;
    if (!name || !name[0] || !isalpha(name[0]))
        return FALSE;
    while (name[i])
    {
        if (!isalnum(name[i]) && name[i] != '_')
            return FALSE;
        i++;
    }
    return TRUE;
}*/
