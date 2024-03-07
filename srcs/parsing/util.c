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

bool	ft_is_redirection(char *token)
{
	return (ft_strcmp(token, "<") == 0 || ft_strcmp(token, "<<") == 0 || \
		ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0);
}

bool	ft_isspace(int c)
{
	return ((c == ' ' || c == '\t' || c == '\n' || c == '\r' \
		|| c == '\f' || c == '\v'));
}
