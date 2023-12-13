#include "minishell.h"

void ft_execute_command_with_absolute_path(t_command *command)
{
    if (execve(command->name, command->args, NULL) == -1) {
            perror("Error executing absolute path");
            exit(EXIT_FAILURE);  
    }
}

void ft_execute_command_with_relative_path(t_command *command){
    char *current_path = getcwd(NULL, 0);
    if (current_path == NULL) {
        perror("Error executing relative path");
        exit(EXIT_FAILURE);
    }
        
    char *full_path = malloc(strlen(current_path) + strlen(command->name) + 2);
    if (full_path == NULL) {
        perror("Erreur d'allocation de mémoire");
        exit(EXIT_FAILURE);
    }

    sprintf(full_path, "%s/%s", current_path, command->name);

    if (access(full_path, X_OK) == 0) {
        if (execve(full_path, command->args, NULL) == -1) {
            perror("Erreur lors de l'exécution de la commande");
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "Command not found: %s\n", full_path);
         exit(EXIT_FAILURE);
    } 
    free(current_path);
    free(full_path);
}

void ft_execute_command_with_path(t_command *command, t_commandList *commandList, t_envList *envList) {
    char *current_path = NULL;
    char *tmp_path = NULL;
    char *full_path = NULL;

    if (command->name[0] == '/') {
        ft_execute_command_with_absolute_path(command);  
    } else if (command->name[0] == '.') {
        ft_execute_command_with_relative_path(command);   
    } 
}

char ft_lookfor_command_and_build_path(const char *path, t_commandList *commandList, t_env *env) {
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
                return strdup(fullPath);
            }
            currentCommand = currentCommand->next;
        }
        currentCommand = commandList->head;
        // go to next token bro
        token = ft_strtok(NULL, ":");
    }
}

