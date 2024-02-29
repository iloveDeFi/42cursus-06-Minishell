#include "minishell.h"

int g_exit_code = 0;

int main(int ac, char **av, char **envp)
{
    t_mini shell;
    t_env *envList;
    t_commandList commandList;

    (void)av;
    if (ac > 1)
    {
        perror("CHAOS, there are too many arguments\n");
        return 1;
    }
    envList = NULL;
    ft_initialize_minishell(&shell);
    ft_initialize_environment(&envList, envp);
    init_termios();
    ft_execute_minishell(&commandList, &shell, envList, envp);
    ft_free_envList(envList);
    ft_exit_shell(&shell);
    return 0;
}