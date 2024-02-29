/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienbelda <julienbelda@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:11:59 by bbessard          #+#    #+#             */
/*   Updated: 2024/02/29 18:28:55 by julienbelda      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
https://koor.fr/C/cstring/strlen.wp
*/

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}
