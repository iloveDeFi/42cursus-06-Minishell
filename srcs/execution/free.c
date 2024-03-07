/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelda <jbelda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:50:41 by jbelda            #+#    #+#             */
/*   Updated: 2024/03/07 18:50:42 by jbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_destroy_current_shell(t_mini *mini)
{
	if (mini->av == NULL)
	{
		free(mini->av);
	}
	if (mini->error != NULL)
	{
		free(mini->error);
	}
}

void	ft_free_redirection_info(t_redirection_info *redirection_info)
{
	free(redirection_info->filename);
	free(redirection_info->delimiter);
}

void	ft_exit_shell(t_mini *shell)
{
	if (shell != NULL)
	{
		if (shell->av != NULL)
			free(shell->av);
	}
}

void	ft_free_split(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
