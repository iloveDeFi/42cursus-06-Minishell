#include "minishell.h"

// char	**ft_env_duplicate(char **envp)
// {
// 	int		i;
// 	char	**copy;

// 	i = 0;
// 	while (envp[i])
// 		i++;
// 	copy = (char **)malloc(sizeof(char *) * (i + 1));
// 	if (!copy)
// 		return (NULL);
// 	i = 0;
// 	while (envp[i])
// 	{
// 		copy[i] = ft_strdup(envp[i]);
// 		if (!copy[i])
// 		{
// 			while (i > 0)
// 			{
// 				free(copy[i - 1]);
// 				i--;
// 			}
// 			free(copy);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	copy[i] = NULL;
// 	return (copy);
// }

int ft_envp_size(char **envp)
{
    int size = 0;
    while (envp[size])
        size++;
    return size;
}

char **ft_envp_duplicate_strings(char **envp, int size)
{
    char **copy = (char **)malloc(sizeof(char *) * (size + 1));
    if (!copy)
        return NULL;

    int i = 0;
    while (i < size)
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
    copy[size] = NULL;
    return copy;
}

char **ft_env_duplicate(char **envp)
{
    int size = ft_envp_size(envp);
    if (size == 0)
        return NULL;

    return ft_envp_duplicate_strings(envp, size);
}
