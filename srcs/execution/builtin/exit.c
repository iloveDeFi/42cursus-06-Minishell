/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelda <jbelda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:47:22 by jbelda            #+#    #+#             */
/*   Updated: 2024/03/07 18:47:28 by jbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_command *command)
{
	int	exit_status;

	if (command->args[1] == NULL)
		exit_status = g_exit_code;
	else if (ft_isnumber(command->args[1]))
		exit_status = ft_atoi(command->args[1]);
	else
	{
		perror("exit\n");
		exit(EXIT_FAILURE);
	}
	if (exit_status < 0)
		exit_status = -exit_status;
	exit(exit_status % 256);
}
