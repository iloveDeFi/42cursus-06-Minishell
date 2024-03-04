#include "minishell.h"

int	g_exit_code = 0;

int	main(int ac, char **av, char **envp)
{
	t_mini			shell;
	t_env			*envlist;
	t_commandList	commandlist;

	(void)av;
	if (ac > 1)
	{
		perror("CHAOS, there are too many arguments\n");
		return (1);
	}
	envlist = NULL;
	ft_init_termios();
	ft_initialize_minishell(&shell);
	ft_initialize_environment(&envlist, envp);
	ft_execute_minishell(&commandlist, &shell, envlist, envp);
	ft_free_envlist(envlist);
	ft_exit_shell(&shell);
	return (0);
}
