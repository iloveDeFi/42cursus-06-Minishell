/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelda <jbelda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:50:38 by jbelda            #+#    #+#             */
/*   Updated: 2024/03/07 18:50:38 by jbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_only_spaces(const char *str)
{
	while (*str)
	{
		if (*str != ' ')
		{
			return (false);
		}
		str++;
	}
	return (true);
}

void	ft_handle_only_spaces(t_mini *shell)
{
	if (ft_is_only_spaces(shell->av))
	{
		ft_destroy_current_shell(shell);
		return ;
	}
}

void	ft_check_null_av_shell(t_mini *shell)
{
	if (shell->av == NULL)
	{
		perror("av == NULL\n");
		exit(EXIT_FAILURE);
	}
}

void	ft_check_empty_av_shell(t_mini *shell)
{
	if (shell->av == NULL)
	{
		exit(EXIT_FAILURE);
	}
}
