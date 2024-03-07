/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelda <jbelda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:47:36 by jbelda            #+#    #+#             */
/*   Updated: 2024/03/07 18:47:38 by jbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

int	main(int ac, char **av, char **envp)
{
	t_mini			shell;
	t_env			*envlist;

	(void)av;
	if (ac > 1)
	{
		perror("CHAOS, there are too many arguments\n");
		return (1);
	}
	envlist = NULL;
	ft_initialize_minishell(&shell);
	ft_initialize_environment(&envlist, envp);
	ft_init_termios();
	ft_execute_minishell(&shell, envlist, envp);
	ft_free_envlist(envlist);
	ft_exit_shell(&shell);
	return (0);
}
