
#include "minishell.h"

void ft_exit_shell(t_mini *shell)
{
    if (shell->av)
        free(shell->av);
}

//before calling function set head and tail to NULL and length to 0
/*void ft_initialize_environment(t_envList *envList, char **env)
{
    int i;
    char **var_array;
    t_env *newNode;

    newNode = NULL;
    var_array = ft_env_duplicate(env);
    i = 0;
    while (var_array[i])
    {
        newNode = ft_createNode(var_array[i]);
        if (!envList)
            envList = &newNode;
        else 
            appendToList(envList, newNode);
        i++;
    }
    free_array(var_array);
}*/

void ft_initialize_environment(t_envList *envList, char **env)
{
    int i;
    char **var_array;
    t_node *newNode;  // Modifier le type de newNode pour t_node

    envList->head = NULL;  // Assurez-vous que envList->head est initialisé à NULL
    var_array = ft_env_duplicate(env);
    i = 0;
    while (var_array[i])
    {
        newNode = ft_createNode(var_array[i]);
        appendToList(&(envList->head), newNode);  // Passez l'adresse de envList->head
        i++;
    }
    free_array(var_array);
}



void ft_initialize_minishell(t_mini *shell, t_env **env)
{
    *env = NULL;
    shell->av = NULL;
    shell->numberOfCommands = 0;
    shell->fd_history = 0;
    shell->status = 0;
    shell->stdin_fd = dup(STDIN_FILENO);
    shell->stdout_fd = dup(STDOUT_FILENO);
    //g_status.infork = NO;
    //g_status.status = 0;
    shell->child = NULL;
    shell->exec = NULL;
    shell->errors = NULL;
    write_inputrc();
}
