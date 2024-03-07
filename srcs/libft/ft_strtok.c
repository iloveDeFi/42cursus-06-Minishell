/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelda <jbelda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:57:04 by bat               #+#    #+#             */
/*   Updated: 2024/03/07 15:37:56 by jbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strtok(char *str, const char *delim)
// {
// 	static char *token = NULL;
// 	if (str != NULL)
// 		token = str;
// 	else if (token == NULL)
// 		return (NULL);
// 	char *start = token;
// 	while (*token != '\0')
// 	{
// 		const char *d = delim;
// 		while (*d != '\0')
// 		{
// 			if (*token == *d)
// 			{
// 				*token = '\0';
// 				token++;
// 				return (start);
// 			}
// 			d++;
// 		}
// 		token++;
// 	}
// 	token = NULL;
// 	return (start);
// }

// char	*ft_strtok(char *str, const char *delim)
// {
// 	static char *token;
// 	char *start;
// 	const char *d;

// 	token = NULL;
// 	if (str != NULL)
// 		token = str;
// 	else if (token == NULL)
// 		return (NULL);
// 	start = token;
// 	while (*token != '\0')
// 	{
// 		d = delim;
// 		while (*d != '\0')
// 		{
// 			if (*token == *d)
// 			{
// 				*token = '\0';
// 				token++;
// 				return (start);
// 			}
// 			d++;
// 		}
// 		token++;
// 	}
// 	token = NULL;
// 	return (start);
// }