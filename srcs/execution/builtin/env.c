/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelda <jbelda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:52:07 by jbelda            #+#    #+#             */
/*   Updated: 2024/03/07 18:52:07 by jbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_display_envlist(t_env *envList)
{
	t_env	*current;

	current = envList;
	while (current != NULL)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}

int	env(t_env *envList)
{
	if (!envList)
		return (EXIT_FAILURE);
	ft_display_envlist(envList);
	return (0);
}
