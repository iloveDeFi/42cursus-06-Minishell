/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienbelda <julienbelda@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 01:12:23 by bat               #+#    #+#             */
/*   Updated: 2023/11/16 13:41:24 by julienbelda      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pwd(void)
{
    char path[PATH_MAX];

    if (getcwd(path, PATH_MAX) != NULL)
    {
        printf("%s\n", path);
        return EXIT_SUCCESS; // ou un autre code de sortie approprié
    }
    else
    {
        perror("[ERROR] : PWD command failed");
        return EXIT_FAILURE; // ou un autre code de sortie approprié
    }
}

