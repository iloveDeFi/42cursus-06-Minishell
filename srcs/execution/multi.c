#include "minishell.h"

void	ft_handle_exit_status(int exit_status)
{
	if (WIFEXITED(exit_status))
		g_exit_code = WEXITSTATUS(exit_status);
}

void	ft_launch_command(t_mini *shell, struct s_command *command)
{
	if (!ft_is_builtin(command))
		ft_execute_external_command(command->envp, command);
	exit(ft_execute_builtin(command, command->envList));
}

void	ft_setup_fd(struct s_command *command, int *fd_pipe_read_tmp,
				int *fd_pipe)
{
	close(fd_pipe[0]);
	if (command->fdread == 0)
		command->fdread = *fd_pipe_read_tmp;
	dup2(command->fdread, 0);
	if (command->fdwrite >= 3)
		close(fd_pipe[1]);
	else if (!command->next)
		command->fdwrite = 1;
	else
		command->fdwrite = fd_pipe[1];
	dup2(command->fdwrite, 1);
}

void	ft_close_fd(struct s_command *command, int *fd_pipe_read_tmp,
				int *fd_pipe)
{
	close(fd_pipe[1]);
	if (*fd_pipe_read_tmp >= 3)
		close(*fd_pipe_read_tmp);
	if (command->fdwrite >= 3)
		close(command->fdwrite);
	if (command->fdread >= 3)
		close(command->fdread);
	*fd_pipe_read_tmp = fd_pipe[0];
}

void	ft_execute_multi_commands(t_mini *mini)
{
	int					fd_pipe_read_tmp;
	int					fd_pipe[2];
	int					exit_status;
	pid_t				pid;
	struct s_command 	*cmd;

	cmd = mini->cmd;
	fd_pipe_read_tmp = 0;
	while (cmd)
	{
		pipe(fd_pipe);
		pid = fork();
		if (pid == 0)
		{
			ft_setup_fd(cmd, &fd_pipe_read_tmp, fd_pipe);
			ft_launch_command(mini, cmd);
		}
		ft_close_fd(cmd, &fd_pipe_read_tmp, fd_pipe);
		cmd = cmd->next;
	}
	while (waitpid(-1, &exit_status, 0) > 0)
		;
	ft_handle_exit_status(exit_status);
}
