/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thfavre@student.42lausanne.ch>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:20:57 by bbessard          #+#    #+#             */
/*   Updated: 2024/03/06 18:52:41 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFFER_SIZE 1

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <string.h>
# include <stdarg.h>
# include <fcntl.h>

/* is_ */
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isnumber(char *str);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_repeat_alpha(char c);

/* str_ */
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);
char			*ft_strjoin(char const	*s1, char const *s2);
char			*ft_strjoin_sep(char const *s1, char const *s2, char sep);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strtok(char *str, const char *delim);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_epur_str(const char *str);
char			**ft_split(char const *s, char c);
char			*ft_strtrim(char const *s1, char const *set);
int				ft_hidenp(const char *str1, const char *str2);
char			*add_letter_to_string(char const *s1, char const letter);
char			*ft_strcat(char *dest, const char *src);

/* mem_*/
void			*ft_memset(void *s, int c, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);

/* A to B */
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_atoi(const char *nptr);
char			*ft_itoa(int n);

/* maths */
void			ft_fprime(int num);
unsigned int	ft_lcm(unsigned int a, unsigned int b);
unsigned int	ft_pgcd(unsigned int a, unsigned int b);
void			ft_tab_mult(int num);

/* _fd */
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

/* get line */
char			*ft_strjoin_gnl(char const *s1, char const *s2);
char			*get_next_line(int fd);

#endif
