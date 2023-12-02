
#include "minishell.h"

int ft_is_builtins(t_command *cmd)
{
    if (!cmd->name)
    {
        ft_putstr_fd("command not found\n", 2);
        return (127);
    }
    if (ft_strcmp(cmd->name, "cd") == 0 
        || ft_strcmp(cmd->name, "echo") == 0 
        || ft_strcmp(cmd->name, "env") == 0
        || ft_strcmp(cmd->name, "exit") == 0
        || ft_strcmp(cmd->name, "export") == 0
        || ft_strcmp(cmd->name, "pwd") == 0
        || ft_strcmp(cmd->name, "unset") == 0)
        return (1);
    return(0); 
}

int ft_exec_builtins(t_command *cmd,t_env **envList)
{
    if (ft_strcmp(cmd->name, "cd") == 0) 
        return cd(cmd->args);
    else if (ft_strcmp(cmd->name, "echo") == 0) 
        return echo(&cmd);
    else if (ft_strcmp(cmd->name, "env") == 0)
        return ft_env(envList);
    else if (ft_strcmp(cmd->name, "pwd") == 0)
        return pwd();
    else if (ft_strcmp(cmd->name, "export") == 0)
    {    // Convertissez cmd->args en un objet t_command
        t_command export_command;
        export_command.name = "export";  // ou utilisez le nom réel de votre choix
        export_command.args = cmd->args;
        export_func(envList, &export_command);
    } 


    // Si le nom de la commande n'est pas reconnu, affichez un message d'erreur
    fprintf(stderr, "Unknown builtin command: %s\n", cmd->name);
    return -1;
}
    
    // t_env *envList = NULL;
    
    // if (ft_is_builtins(cmd)) {
    //     if (ft_strcmp(cmd->name, "cd") == 0)
    //         return cd(cmd->args); // Appel de la fonction cd
    //     else if (ft_strcmp(cmd->name, "echo") == 0)
    //         return echo(cmd->args); // Appel de la fonction echo
    //     else if (ft_strcmp(cmd->name, "env") == 0)
    //         return ft_env(&envList); // Appel de la fonction env
    //     // // else if (ft_strcmp(cmd->name, "exit") == 0)
    //     // //     return ft_exit(cmd->args); // Appel de la fonction exit
    //     // else if (ft_strcmp(cmd->name, "export") == 0)
    //     //     return export_func(cmd->args); // Appel de la fonction export
    //     // else if (ft_strcmp(cmd->name, "pwd") == 0)
    //     //     return ft_pwd(cmd->args); // Appel de la fonction pwd
    //     // // else if (ft_strcmp(cmd->name, "unset") == 0)
    //     // //     return ft_unset(cmd->args); // Appel de la fonction unset
    // } else {
    //         ft_putstr_fd("Command not recognized\n", 2);
    //         g_exit_code = 127;
    //     }
    // return (g_exit_code);
