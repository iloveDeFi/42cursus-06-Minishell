/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:57:04 by bat               #+#    #+#             */
/*   Updated: 2023/10/21 13:40:57 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strtok(char *str, const char *delim) 
{
    static char *token = NULL;
    if (str != NULL) {
        token = str;
    } 
    else if (token == NULL) {
        return NULL;
    }
    char *start = token;
    char *end = ft_stringPointerBreak(token, delim);
    if (end != NULL) {
        *end = '\0';
        token = end + 1;
    } else {
        token = NULL;
    }
    return start;
}
