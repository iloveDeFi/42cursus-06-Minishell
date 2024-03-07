/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelda <jbelda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:51:53 by jbelda            #+#    #+#             */
/*   Updated: 2024/03/07 18:51:53 by jbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(t_command *cmd, t_env *envList, char **envp)
{
	if (cmd->next == NULL)
		ft_execute_cmd(cmd, envp, envList);
	else
	{
		ft_execute_cmds(cmd, envp, envList);
	}
}
