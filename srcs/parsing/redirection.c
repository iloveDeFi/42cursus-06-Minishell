#include "minishell.h"

static bool	ft_open_file(char *filename, int *fd, int flags, mode_t mode)
{
	*fd = open(filename, flags, mode);
	if (*fd == -1)
	{
		perror("minishell: open error");
		g_exit_code = 258;
		return (false);
	}
	return (true);
}

static bool	ft_parse_input_redirection(char *filename, int *fdread)
{
	if (filename == NULL || ft_strcmp(filename, "|") == 0)
	{
		ft_putstr_fd("minishell: parse error near <\n", STDERR_FILENO);
		g_exit_code = 258;
		return (false);
	}
	return (ft_open_file(filename, fdread, O_RDONLY, 0));
}

static bool	ft_parse_output_redirection(char *filename, int *fdwrite, int flags)
{
	if (filename == NULL || ft_strcmp(filename, "|") == 0)
	{
		ft_putstr_fd("minishell: parse error near >\n", STDERR_FILENO);
		g_exit_code = 258;
		return (false);
	}
	return (ft_open_file(filename, fdwrite, flags, 0644));
}

static bool ft_parse_heredoc_redirection(char filename, int fdread) {
    if (filename == NULL || ft_strcmp(filename, "|") == 0) {
        ft_putstr_fd("minishell: parse error near <<\n", STDERR_FILENO);
        g_exit_code = 258;
        return false;
    }
    ft_exec_heredoc(filename, fdread);
    return true;
}

bool	ft_parse_all_redirection(char *redir, char *filename, \
	int *fdread, int *fdwrite)
{
	if (ft_strcmp(redir, "<") == 0)
		return (ft_parse_input_redirection(filename, fdread));
	else if (ft_strcmp(redir, ">") == 0)
		return (ft_parse_output_redirection(filename, \
			fdwrite, O_CREAT | O_WRONLY | O_TRUNC));
	else if (ft_strcmp(redir, ">>") == 0)
		return (ft_parse_output_redirection(filename, \
			fdwrite, O_CREAT | O_WRONLY | O_APPEND));
	else if (ft_strcmp(redir, "<<") == 0)
		return (ft_parse_heredoc_redirection(filename, fdread));
	return (true);
}
