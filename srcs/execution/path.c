#include "minishell.h"

/* 

// char *get_path(t_env *envList) 
// {
// 	while (envList != NULL) 
// 	{
// 		if (ft_strcmp(envList->var, "PATH") == 0) 
// 		{
// 			return envList->value;
// 		}
// 		envList = envList->next;
// 	}
// 	return NULL;  // Si PATH n'est pas trouvé
// }

// // Modification de la fonction dans le fichier source
// // path.c

// char    *find_executable(char *command, t_pathList *pathList) 
// {
// 	t_pathNode *current;
	
// 	current = pathList->head;
// 	while (current != NULL) 
// 	{
// 		// Construire le chemin complet du fichier exécutable
// 		char executable_path[256];
// 		// Copier le répertoire courant dans le chemin
// 		ft_strcpy(executable_path, current->directory);
// 		// Concaténer la barre oblique et la commande à la fin du chemin
// 		ft_strcat(executable_path, "/");
// 		ft_strcat(executable_path, command);
// 		// Vérifier si le fichier exécutable existe
// 		if (access(executable_path, X_OK) == 0) 
// 		{
// 			printf("Executable found: %s\n", command);
// 			return ft_strdup(command);
// 		}
// 		else
// 			printf("Executable not found in the path: %s\n", executable_path);
// 		current = current->next;
// 	}
// 	return (NULL);  // Si la commande n'est pas trouvée dans le PATH
// }

// void    initializePathList(t_pathList *pathList, const char *path) 
// {
// 	char    *token;
	
// 	pathList->head = NULL;
// 	if (path != NULL) 
// 	{
// 		token = ft_strtok((char *)path, ":");
// 		while (token != NULL) 
// 		{
// 			// Ajouter le répertoire à la liste
// 			t_pathNode *node = malloc(sizeof(t_pathNode));
// 			node->directory = ft_strdup(token);
// 			node->next = pathList->head;
// 			pathList->head = node;
// 			token = ft_strtok(NULL, ":");
// 		}
// 	}
// }

// void	freePathList(t_pathList *pathList)
// {
// 	t_pathNode	*current;
// 	t_pathNode	*next;

// 	current = pathList->head;
// 	while (current != NULL)
// 	{
// 		next = current->next;
// 		free(current->directory);
// 		free(current);
// 		current = next;
// 	}
// }


Dans léxecution condition qui check si commande commence par . ou / 
si oui code pour la gestion du Path
call ft_execute_path()

if (cmd[0] == '.'|| cmd[0] == '/') {
    ft_execute_path()
}
*/

/*int ft_execute_path(t_commandList *command, const char *path)
{
    const char *myPath;

    myPath = getenv("PATH");
    if (myPath != NULL) {

    }
    else {
        perror("PATH isn't defined");
    }
    return (0);
}*/

// TO DO dans ft_execute_external_command
// ft_find_executable_path(cmdPath, envList);

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
                printf("Command '%s' found: %s\n", command, fullPath);
            // Ici, vous pouvez appeler la fonction d'exécution de la commande
            // (par exemple, execve, system, etc.).
                ft_exec_cmd(currentCommand->name, env);
                return;
            }
            currentCommand = currentCommand->next;
        }
        currentCommand = commandList->head;
        // go to next token bro
        token = ft_strtok(NULL, ":");
    }
}

char *ft_find_executable_path(const char *command, t_env *envList) {
    // Si le chemin est absolu, essayez de l'exécuter directement
    if (access(command, F_OK | X_OK) == 0) {
        return strdup(command);
    }

    // Obtenez la valeur de la variable d'environnement PATH
    t_env *path_env = get_in_lst("PATH", &envList);
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
            free_split(path_directories);
            return full_path;
        }

        free(full_path);
        full_path = NULL;
        i++;
    }

    free_split(path_directories);
    return NULL;
}

