/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 01:03:24 by bat               #+#    #+#             */
/*   Updated: 2023/11/04 21:22:23 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_signal(int signal_num) {
    if (signal_num == SIGINT)
    {
        printf("\nSignal SIGINT received. Stopping the current process.\n");
        exit(EXIT_SUCCESS);    
    }
    else if (signal_num == SIGQUIT)
    {
        
    }
}
