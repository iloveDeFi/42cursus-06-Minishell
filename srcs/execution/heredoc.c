#include "minishell.h"

/* creates the heredoc and executes it */
void ft_process_here_doc_redirection(t_command *command) 
{
	char	*here;
	int		heredoc;

	heredoc = open(".heredoc.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (!heredoc)
	{
		perror("error creating heredoc file");
		return ;
	}
	here = readline(">");
	while (here && !ft_eof_is_in_string(here, command->end_of_file))
	{
		write(heredoc, here, ft_strlen(here));
		write(heredoc, "\n", 1);
		free(here);
		here = readline(">");
	}
	close(heredoc);
	free(here);
	command->fdread = open(".heredoc.txt", O_RDONLY);
}

/* returns true if EOF is contained in the string */
int	ft_eof_is_in_string(char *here, char *eof)
{
	if (ft_isword(here, eof, 0))
		return (1);
	return (0);
}

/* returns true if the word is found */
int	ft_isword(char *here, char *eof, int index)
{
	int	i;

	i = -1;
	while (eof[++i])
	{
		if (eof[i] == here[index])
			index++;
		else
			return (0);
	}
	return (1);
}