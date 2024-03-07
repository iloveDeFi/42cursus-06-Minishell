/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelda <jbelda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:50:56 by jbelda            #+#    #+#             */
/*   Updated: 2024/03/07 18:50:57 by jbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_path(char **env)
{
	char	*path;
	char	**splited_path;

	(void)env;
	path = getenv("PATH");
	if (path[0] == '\0')
	{
		free(path);
		return (NULL);
	}
	splited_path = ft_split(path + 5, ':');
	return (splited_path);
}
