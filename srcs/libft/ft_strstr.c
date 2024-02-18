/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbessard <bbessard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:21:44 by bbessard          #+#    #+#             */
/*   Updated: 2024/02/18 16:24:14 by bbessard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *ft_str_str(const char *haystack, const char *needle) 
{
    const char *h;
    const char *n;

    if (*needle == '\0') {
        return (char *)haystack;
    }

    while (*haystack != '\0') {
        h = haystack;
        n = needle;

        while (*h != '\0' && *n != '\0' && *h == *n) {
            h++;
            n++;
        }

        if (*n == '\0') {
            return (char *)haystack;
        }

        haystack++;
    }

    return NULL;
}