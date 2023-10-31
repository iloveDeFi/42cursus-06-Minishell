/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stringPointerBreak.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 13:16:41 by bat               #+#    #+#             */
/*   Updated: 2023/10/31 23:42:11 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *stringPointerBreak(const char *str1, const char *str2) 
{
    const char *search = str2;
    
    while (*str1 != '\0') {
        while (*search != '\0') {
            if (*str1 == *search) {
                return (char *)str1;
            }
            search++;
        }
        str1++;
    }
    return NULL;
}
