/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelda <jbelda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:50:45 by jbelda            #+#    #+#             */
/*   Updated: 2024/03/07 18:50:53 by jbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_heredoc(char *end_of_file, int *fdread)
{
	char	*here;
	int		heredoc;

	heredoc = open(".heredoc.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
	here = readline(">");
	while (here && !ft_eof_is_in_string(here, end_of_file))
	{
		write(heredoc, here, ft_strlen(here));
		write(heredoc, "\n", 1);
		free(here);
		here = readline(">");
		rl_redisplay();
		add_history(here);
	}
	close(heredoc);
	*fdread = open(".heredoc.txt", O_RDONLY);
	return ;
}

int	ft_eof_is_in_string(char *here, char *eof)
{
	if (ft_find_word(here, eof, 0))
		return (1);
	return (0);
}

int	ft_find_word(char *here, char *eof, int index)
{
	int	i;

	i = -1;
	while (eof[++i])
	{
		if (eof[i] == here[index])
			index++;
		else
			return (0);
	}
	return (1);
}
