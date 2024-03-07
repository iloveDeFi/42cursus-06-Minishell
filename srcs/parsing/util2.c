/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelda <jbelda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:49:28 by jbelda            #+#    #+#             */
/*   Updated: 2024/03/07 18:49:29 by jbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_free_toks(t_token **tokens)
{
	ft_putstr_fd("Error: unclosed quote\n", STDERR_FILENO);
	ft_free_tokens(tokens);
}
