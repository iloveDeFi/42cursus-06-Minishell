/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 01:11:52 by bat               #+#    #+#             */
/*   Updated: 2023/10/16 16:19:01 by bat              ###   ########.fr       */
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