#include "minishell.h"

void ft_execute_command_with_path(const char *path, t_commandList *commandList, t_env *env) {
    char *token;
    char fullPath[MAX_PATH_LENGTH];

    t_command *currentCommand = commandList->head;

    token = ft_strtok((char *)path, ":");
    while (token != NULL) 
    {
        while (currentCommand != NULL) 
        {
            ft_strcpy(fullPath, token);
            ft_strcat(fullPath, "/");
            ft_strcat(fullPath, currentCommand->name);
            if (access(fullPath, X_OK) == 0) 
            {
                printf("Command '%s' found: %s\n", currentCommand->name, fullPath);
                // Ici, vous pouvez appeler la fonction d'exécution de la commande
                // (par exemple, execve, system, etc.).
                ft_exec_cmd(fullPath, env);
                return;
            }
            currentCommand = currentCommand->next;
        }
        currentCommand = commandList->head;
        // passer au jeton suivant
        token = ft_strtok(NULL, ":");
    }
}


char *ft_find_executable_path(const char *command, t_env *envList) {
    // Si le chemin est absolu, essayez de l'exécuter directement
    if (access(command, F_OK | X_OK) == 0) {
        return strdup(command);
    }

    // Obtenez la valeur de la variable d'environnement PATH
    t_env *path_env = ft_get_in_list("PATH", &envList);
    if (path_env == NULL) {
        fprintf(stderr, "Error: PATH variable not found in environment\n");
        return NULL;
    }

    // Utilisez execvp pour essayer d'exécuter la commande avec le chemin du système
    char **path_directories = ft_split(path_env->value, ':');
    char *full_path = NULL;
    int i = 0;

    while (path_directories[i] != NULL) {
        full_path = ft_strjoin(path_directories[i], "/");
        full_path = ft_strjoin_free(full_path, command, 1);

        if (access(full_path, F_OK | X_OK) == 0) {
            ft_free_split(path_directories);
            return full_path;
        }

        free(full_path);
        full_path = NULL;
        i++;
    }

    ft_free_split(path_directories);
    return NULL;
}

