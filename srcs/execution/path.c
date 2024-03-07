#include "minishell.h"

char	**ft_split_path(char **env)
{
	char	*path;
	char	**splited_path;

	(void)env;
	path = getenv("PATH");
	if (path[0] == '\0')
	{
		free(path);
		return (NULL);
	}
	splited_path = ft_split(path + 5, ':');
	return (splited_path);
}
