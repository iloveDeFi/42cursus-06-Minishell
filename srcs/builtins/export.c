/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienbelda <julienbelda@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 01:12:19 by bat               #+#    #+#             */
/*   Updated: 2023/11/11 00:05:10 by julienbelda      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_error_export(char *args)
{
    ft_putstr_fd("export: ", STDERR_FILENO);
    ft_putstr_fd(args, STDERR_FILENO);
    ft_putstr_fd(" : Identifer not valid\n", STDERR_FILENO);
    return (EXIT_FAILURE);
}

int ft_check_wrong_char(char *str)
{
    int i;

    i = 0;
    if (str[i] == '=')
        return (0);
    while (str[i])
    {
        if (ft_is_sep(str[i]) || (str[i] >= 33 && str[i] <= 47)
            || (str[i] == '=' && str[i + 1] == '='))
            return (TRUE);
        i++; 
    }
    return (FALSE);   
}
