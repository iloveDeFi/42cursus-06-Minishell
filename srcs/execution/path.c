#include "minishell.h"

void ft_execute_command_with_path(t_command *command, t_commandList *commandList, t_envList *envList) {
    
    char *current_path;
    char *tmp_path;
    char *full_path;

    if (command->name[0] == '/'){
        if (execve() == -1){
            return error;
        } 
    }
    else if (command->name[0] == '.'){
        current_path = getcwd();
        tmp_path = ft_strjoin(current_path, '/');
        full_path = ft_strjoin(tmp_path, command->name);
        if (access(full_path, X_OK) == 0){
            execve()
        }
        else 
            return error;
    }
}
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

