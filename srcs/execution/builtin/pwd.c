/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelda <jbelda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:52:24 by jbelda            #+#    #+#             */
/*   Updated: 2024/03/07 18:52:25 by jbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	path[MAXPATHLEN];

	if (getcwd(path, MAXPATHLEN) != NULL)
	{
		printf("%s\n", path);
		return (EXIT_SUCCESS);
	}
	else
	{
		perror("[ERROR] : PWD command failed");
		return (EXIT_FAILURE);
	}
}
