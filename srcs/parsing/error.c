#include "minishell.h"

int	ft_str_error(char *str, int number)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (number);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}