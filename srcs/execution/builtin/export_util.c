/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelda <jbelda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:52:14 by jbelda            #+#    #+#             */
/*   Updated: 2024/03/07 18:52:15 by jbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

void	ft_split_string_export_argument(const char *arg, \
	char **name, char **value)
{
	char	*equals;

	equals = ft_strchr(arg, '=');
	if (equals != NULL)
	{
		*equals = '\0';
		*name = ft_strdup(arg);
		*value = ft_strdup(equals + 1);
	}
	else
	{
		*name = NULL;
		*value = NULL;
	}
}
