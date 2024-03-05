#include "minishell.h"

int	pwd(void)
{
	char	path[MAXPATHLEN];

	if (getcwd(path, MAXPATHLEN) != NULL)
	{
		printf("%s\n", path);
		return (EXIT_SUCCESS);
	}
	else
	{
		perror("[ERROR] : PWD command failed");
		return (EXIT_FAILURE);
	}
}
