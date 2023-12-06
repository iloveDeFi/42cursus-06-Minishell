#include "minishell.h"

int	change_directory(const char *path)
{
	char	*pwd;

	if (chdir(path) == 0)
	{
		pwd = getcwd(NULL, 0);
		setenv("PWD", pwd, 1);
		free(pwd);
		return (0);
	}
	else
	{
		fprintf(stderr, "cd: %s: No such file or directory\n", path);
		return (-1);
	}
}

int	cd(char **arguments)
{
	char	*home_directory;

	if (arguments == NULL || arguments[1] == NULL)
	{
		home_directory = ("HOME");
		if (home_directory != NULL)
		{
			return (chdir(home_directory));
		}
		else
		{
			perror("cd");
			return (-1);
		}
	}
	else
		return (chdir(arguments[1]));
}
