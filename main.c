/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 01:11:52 by bat               #+#    #+#             */
/*   Updated: 2023/10/20 19:53:24 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
    if (ac > 1)
        return (str_error("Oops, there are too many arguments", 0));
    while (1)
    {
        printf("Mon shell> ");
        exit_shell();
        return (0);
        
    }
}
