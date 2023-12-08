#include "minishell.h"

int ft_echo(t_command **args)
{
    const char *message = "An error occurred: not enough arguments\n";
    int i = 0;
    bool no_newline = false;

    if (args == NULL || args[0] == NULL || args[0]->args == NULL)
    {
        write(STDERR_FILENO, message, strlen(message));
        return (1);
    }

    // Check for the -n flag
    if (args[0]->argCount > 1 && strcmp(args[0]->args[1], "-n") == 0)
    {
        no_newline = true;
        i = 1; // Skip the -n flag
    }

	while (args[0]->args[i] != NULL)
	{
		if (args[0]->args[i] != NULL)
		{
			write(STDOUT_FILENO, args[0]->args[i], strlen(args[0]->args[i]));

			if (args[0]->args[i + 1] != NULL)
				write(STDOUT_FILENO, " ", 1);
		}

		i++;
	}


    if (!no_newline)
        write(STDOUT_FILENO, "\n", 1);

    return 0;
}
