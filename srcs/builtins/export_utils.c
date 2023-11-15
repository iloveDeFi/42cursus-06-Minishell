#include "minishell.h" 

int	ft_is_sep(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

char **ft_env_duplicate(char **envp)
{
    char **copy;
    int i = 0;

    while (envp[i])
        i++;
    copy = (char **)malloc(sizeof(char *) * (i + 1));
    if (!copy)
        return NULL;
    i = 0;
    while (envp[i])
    {
        copy[i] = ft_strdup(envp[i]);
        if (!copy[i])
        {
            while (i > 0)
            {
                free(copy[i - 1]);
                i--;
            }
            free(copy);
            return NULL;
        }
        i++;
    }
    copy[i] = NULL;
    return copy;
}
