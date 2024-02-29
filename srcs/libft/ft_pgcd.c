/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pgcd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienbelda <julienbelda@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:58:55 by bbessard          #+#    #+#             */
/*   Updated: 2024/02/29 18:22:50 by julienbelda      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**  Plus Grand Common Divider = PGCD
*/

#include "libft.h"

unsigned int	ft_pgcd(unsigned int a, unsigned int b)
{
	unsigned int	tmp;

	if (a <= 0 || b <= 0)
	{
		printf("\n");
		return (0);
	}
	while (b != 0)
	{
		tmp = b;
		b = a % b;
		a = tmp;
	}
	return (a);
}
