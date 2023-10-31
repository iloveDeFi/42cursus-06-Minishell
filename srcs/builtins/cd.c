/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 01:11:44 by bat               #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/10/26 11:13:37 by julien           ###   ########.fr       */
=======
/*   Updated: 2023/10/30 10:27:15 by julien           ###   ########.fr       */
>>>>>>> julien
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
int	change_directory(const char *path)
=======
/*int	change_directory(const char *path)
>>>>>>> julien
{
	char	*pwd;

	if (chdir(path) == 0)
	{
		pwd = getcwd(NULL, 0);
		setenv("PWD", pwd, 1);
		free(pwd);
		return (0);
	}
	else
	{
		perror("cd");
		return (-1);
	}
}

<<<<<<< HEAD
int	cd(t_command *command, t_envList *envList)
=======
int cd(t_command *command, t_envList *envList)
>>>>>>> julien
{
	char	*home_directory;

	if (command->arguments == NULL || command->arguments[1] == NULL)
	{
		home_directory = getenv("HOME");
		if (home_directory != NULL)
		{
			return (change_directory(home_directory));
		}
		else
		{
			perror("cd");
			return (-1);
		}
	}
	else
	{
		return (change_directory(command->arguments[1]));
	}
}*/
