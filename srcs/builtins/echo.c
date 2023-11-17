
#include "minishell.h"

int echo(char **arguments) 
{
    const char *message = "An error occured : not enough arguments\n";
    
    if (arguments[1] == NULL) 
    {
        write(STDERR_FILENO, message, strlen(message));
        return 1;  // or another error code according to your convention
    }

    int i = 1;
    while (arguments[i] != NULL) 
    {
        write(STDOUT_FILENO, arguments[i], strlen(arguments[i]));
        if (arguments[i + 1] != NULL)
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    write(STDOUT_FILENO, "\n", 1);

    return 0;  // or another success code according to your convention
}

