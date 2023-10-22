/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 01:12:23 by bat               #+#    #+#             */
/*   Updated: 2023/10/20 19:53:28 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, PATH_MAX) != NULL)
		printf("%s\n", path);
	else
		printf("[ERROR] : PWD command failed");
}
