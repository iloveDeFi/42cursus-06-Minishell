#include "minishell.h"

static void	prepare_fds(t_command *cmd, int *fd_pipe_read_tmp,
				int *fd_pipe)
{
	close(fd_pipe[0]);
	if (cmd->fdread == 0)
		cmd->fdread = *fd_pipe_read_tmp;
	dup2(cmd->fdread, 0);
	if (cmd->fdwrite >= 3)
		close(fd_pipe[1]);
	else if (!cmd->next)
		cmd->fdwrite = 1;
	else
		cmd->fdwrite = fd_pipe[1];
	dup2(cmd->fdwrite, 1);
}

static void	close_fds(t_command *cmd, int *fd_pipe_read_tmp,
				int *fd_pipe)
{
	close(fd_pipe[1]);
	if (*fd_pipe_read_tmp >= 3)
		close(*fd_pipe_read_tmp);
	if (cmd->fdwrite >= 3)
		close(cmd->fdwrite);
	if (cmd->fdread >= 3)
		close(cmd->fdread);
	*fd_pipe_read_tmp = fd_pipe[0];
}

static void	ft_run_cmd(t_command *cmd, char **envp, t_env *envList)
{
	if (!ft_is_builtin(cmd))
		ft_execute_external_command(cmd, envp);
	exit(ft_execute_builtin(cmd, envList));
}

static void	handle_exit_status(int exit_status)
{
	if (WIFEXITED(exit_status))
		g_exit_code = WEXITSTATUS(exit_status);
	if (WIFSIGNALED(exit_status))
		g_exit_code = 128 + WTERMSIG(exit_status);
}

void	ft_execute_cmds(t_command *cmd, char **envp, t_env *envList)
{
	int					fd_pipe_read_tmp;
	int					fd_pipe[2];
	int					exit_status;
	pid_t				fork_pid;

	fd_pipe_read_tmp = 0;
	while (cmd)
	{
		pipe(fd_pipe);
		fork_pid = fork();
		if (fork_pid == 0)
		{
			prepare_fds(cmd, &fd_pipe_read_tmp, fd_pipe);
			ft_run_cmd(cmd, envp, envList);
		}
		close_fds(cmd, &fd_pipe_read_tmp, fd_pipe);
		cmd = cmd->next;
	}
	while (waitpid(-1, &exit_status, 0) > 0)
		;
	handle_exit_status(exit_status);
}
