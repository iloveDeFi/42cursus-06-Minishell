/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 01:11:47 by bat               #+#    #+#             */
/*   Updated: 2023/10/30 10:28:09 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int echo(int ac, char **av)
{
    const char *message = "An error occured : not enough arguments\n";
    if (ac < 2)
    {
        write(STDERR_FILENO, message, strlen(message));
        exit(EXIT_FAILURE);
    }
    int i = 1;
    while (av[i] != NULL)
    {
        write(STDOUT_FILENO, av[i], strlen(av[i]));
        if (av[i + 1] != NULL)
            write(STDOUT_FILENO, " ", 1);
        i++;
    write(STDOUT_FILENO, "\n", 1);
    exit(EXIT_SUCCESS);
    }
    return 0;
}
