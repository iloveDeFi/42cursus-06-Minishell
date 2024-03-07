#include "minishell.h"

/* Returns true if EOF is contained in the string */
int	ft_eof_is_in_string(char *here_doc, char *end_of_file)
{
	return (ft_find_word(here_doc, end_of_file, 0));
}

/* Returns true if the word is found */
int	ft_find_word(char *here_doc, char *end_of_file, int index)
{
	int	i;

	i = 0;
	while (end_of_file[i])
	{
		if (end_of_file[i] == here_doc[index])
		{
			index++;
			i++;
		}
		else
		{
			return (0);
		}
	}
	return (1);
}

/* Creates the heredoc and executes it */
void	ft_process_here_doc_redirection(t_command *command)
{
	char	*here;
	int		heredoc;

	heredoc = open(".heredoc.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (heredoc == -1)
	{
		perror("Error creating heredoc file");
		return ;
	}
	while ((here = readline(">")) && !ft_eof_is_in_string(here, \
		command->end_of_file))
	{
		write(heredoc, here, ft_strlen(here));
		write(heredoc, "\n", 1);
		free(here);
	}
	close(heredoc);
	command->fdread = open(".heredoc.txt", O_RDONLY);
}
