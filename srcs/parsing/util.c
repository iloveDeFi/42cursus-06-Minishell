#include "minishell.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	if (dest == NULL || src == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_custom_strdup(const char *str)
{
	size_t	len;
	char	*copy;

	len = ft_strlen(str);
	copy = malloc(len + 1);
	if (copy == NULL)
	{
		perror("CHAOS, error allocating memory");
		exit(EXIT_FAILURE);
	}
	ft_strcpy(copy, str);
	return (copy);
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		ft_putchar_fd(*s++, fd);
}