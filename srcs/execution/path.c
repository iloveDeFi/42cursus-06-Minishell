#include "minishell.h"

char *get_path(t_env *envList) 
{
	while (envList != NULL) 
	{
		if (ft_strcmp(envList->var, "PATH") == 0) 
		{
			return envList->value;
		}
		envList = envList->next;
	}
	return NULL;  // Si PATH n'est pas trouvé
}

// Modification de la fonction dans le fichier source
// path.c

char    *find_executable(char *command, t_pathList *pathList) 
{
	t_pathNode *current;
	
	current = pathList->head;
	while (current != NULL) 
	{
		// Construire le chemin complet du fichier exécutable
		char executable_path[256];
		// Copier le répertoire courant dans le chemin
		ft_strcpy(executable_path, current->directory);
		// Concaténer la barre oblique et la commande à la fin du chemin
		ft_strcat(executable_path, "/");
		ft_strcat(executable_path, command);
		// Vérifier si le fichier exécutable existe
		if (access(executable_path, X_OK) == 0) 
		{
			printf("Executable found: %s\n", command);
			return ft_strdup(command);
		}
		else
			printf("Executable not found in the path: %s\n", executable_path);
		current = current->next;
	}
	return (NULL);  // Si la commande n'est pas trouvée dans le PATH
}

void    initializePathList(t_pathList *pathList, const char *path) 
{
	char    *token;
	
	pathList->head = NULL;
	if (path != NULL) 
	{
		token = ft_strtok((char *)path, ":");
		while (token != NULL) 
		{
			// Ajouter le répertoire à la liste
			t_pathNode *node = malloc(sizeof(t_pathNode));
			node->directory = ft_strdup(token);
			node->next = pathList->head;
			pathList->head = node;
			token = ft_strtok(NULL, ":");
		}
	}
}

void	freePathList(t_pathList *pathList)
{
	t_pathNode	*current;
	t_pathNode	*next;

	current = pathList->head;
	while (current != NULL)
	{
		next = current->next;
		free(current->directory);
		free(current);
		current = next;
	}
}
