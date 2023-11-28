
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



int ft_exec_builtins(t_command *cmd)
{
    t_env *envList = NULL;
    
    if (ft_strcmp(cmd->name, "cd") == 0)
        g_exit_code = cd(cmd->args);
    else if (ft_strcmp(cmd->name, "echo") == 0)
        g_exit_code = echo(cmd->args);
    else if (ft_strcmp(cmd->name, "env") == 0)
        g_exit_code = ft_env(&envList);
    else if (ft_strcmp(cmd->name, "exit") == 0)
        ft_exit(cmd);
    else if (ft_strcmp(cmd->name, "export") == 0)
        g_exit_code = export_func(&envList, cmd);
    else if (ft_strcmp(cmd->name, "pwd") == 0)
        g_exit_code = pwd();
    else if (ft_strcmp(cmd->name, "unset") == 0)
        g_exit_code = ft_unset(&envList, cmd);
    return (g_exit_code);
}