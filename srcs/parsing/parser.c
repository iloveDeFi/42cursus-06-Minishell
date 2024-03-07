/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelda <jbelda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:48:29 by jbelda            #+#    #+#             */
/*   Updated: 2024/03/07 18:48:30 by jbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*ft_parser(char *input, t_env *envList)
{
	t_command	*commands;
	t_token		**tokens;

	commands = NULL;
	tokens = ft_tokenize(input);
	if (!tokens)
	{
		return (NULL);
	}
	ft_found_and_replace_usd(tokens, envList);
	if (!ft_parse_tokens(&commands, tokens))
	{
		return (NULL);
	}
	return (commands);
}
