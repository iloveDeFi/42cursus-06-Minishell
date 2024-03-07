/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelda <jbelda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:51:40 by jbelda            #+#    #+#             */
/*   Updated: 2024/03/07 18:51:40 by jbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_external_command(t_command *cmd, char **env)
{
	char	filepath[MAX_PATH_LENGTH];
	char	**splited_path;
	int		i;

	if (access(cmd->name, X_OK) == 0)
		execve(cmd->name, cmd->args, env);
	splited_path = ft_split_path(env);
	i = 0;
	while (splited_path && splited_path[i] != NULL)
	{
		ft_strcpy(filepath, splited_path[i]);
		ft_strcat(filepath, "/");
		ft_strcat(filepath, cmd->name);
		if (access(filepath, X_OK) == 0)
		{
			execve(filepath, cmd->args, env);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (splited_path)
		ft_free_split(splited_path);
	ft_putstr_fd(cmd->name, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}
