#include "minishell.h"

void	ft_execute(t_command *cmd, t_env *envList, char **envp)
{
	if (cmd->next == NULL)
		ft_execute_cmd(cmd, envp, envList);
	else
	{
		ft_execute_cmds(cmd, envp, envList);
	}
}
