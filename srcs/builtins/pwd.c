
#include "minishell.h"

int pwd(void)
{
    char path[PATH_MAX];

    if (getcwd(path, PATH_MAX) != NULL)
    {
        printf("%s\n", path);
        return EXIT_SUCCESS; // ou un autre code de sortie approprié
    }
    else
    {
        perror("[ERROR] : PWD command failed");
        return EXIT_FAILURE; // ou un autre code de sortie approprié
    }
}

