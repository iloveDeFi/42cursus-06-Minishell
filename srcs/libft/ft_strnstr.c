/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbessard <bbessard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 13:07:53 by bbessard          #+#    #+#             */
/*   Updated: 2022/11/22 11:29:37 by bbessard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
https://codecogs.com/library/computing/c/string.h/strstr.php?alias=strnstr
"une aiguille (needle) dans une botte de foin (haystack)"
*/

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while ((haystack[i + j]
				&& needle[j] == haystack[i + j]) && (i + j < len))
		{
			if (needle[j + 1] == 0)
				return ((char *)(&haystack[i]));
			j++;
		}
		i++;
	}
	return (NULL);
}
