/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienbelda <julienbelda@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 01:12:29 by bat               #+#    #+#             */
/*   Updated: 2023/11/16 13:18:25 by julienbelda      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_unset(t_envVarList *envVarList, char *arg) {
    int exit_code = 0;
    t_node *current = envVarList->head;
    t_node *prev = NULL;

    while (current) {
        t_envVar *tmp = (t_envVar *)current->data;

        if (tmp != NULL && strcmp(arg, tmp->name) == 0) {
            if (prev == NULL)
                envVarList->head = current->next;
            else
                prev->next = current->next;

            free(tmp->name);
            free(tmp->value);
            free(tmp);
            free(current);
            break;
        }
        prev = current;
        current = current->next;
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
}
