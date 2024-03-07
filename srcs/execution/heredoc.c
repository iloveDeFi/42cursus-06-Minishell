#include "minishell.h"

void	ft_exec_heredoc(char *end_of_file, int *fdread)
{
	char	*here;
	int		heredoc;

	heredoc = open(".heredoc.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
	here = readline(">");
	while (here && !ft_eof_is_in_string(here, end_of_file))
	{
		write(heredoc, here, ft_strlen(here));
		write(heredoc, "\n", 1);
		free(here);
		here = readline(">");
        rl_redisplay();
		add_history(here);
	}
	close(heredoc);
	*fdread = open(".heredoc.txt", O_RDONLY);
	return ;
}

int	ft_eof_is_in_string(char *here, char *eof)
{
	if (ft_find_word(here, eof, 0))
		return (1);
	return (0);
}

int	ft_find_word(char *here, char *eof, int index)
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

/* Returns true if EOF is contained in the string */
// int	ft_eof_is_in_string(char *here_doc, char *end_of_file)
// {
// 	return (ft_find_word(here_doc, end_of_file, 0));
// }

// /* Returns true if the word is found */
// int	ft_find_word(char *here_doc, char *end_of_file, int index)
// {
// 	int	i;

// 	i = 0;
// 	while (end_of_file[i])
// 	{
// 		if (end_of_file[i] == here_doc[index])
// 		{
// 			index++;
// 			i++;
// 		}
// 		else
// 		{
// 			return (0);
// 		}
// 	}
// 	return (1);
// }

// /* Creates the heredoc and executes it */
// void	ft_process_here_doc_redirection(t_command *command)
// {
// 	char	*here;
// 	int		heredoc;

// 	heredoc = open(".heredoc.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
// 	if (heredoc == -1)
// 	{
// 		perror("Error creating heredoc file");
// 		return ;
// 	}
// 	while ((here = readline(">")) && 
// !ft_eof_is_in_string(here, \
// 		command->end_of_file))
// 	{
// 		write(heredoc, here, ft_strlen(here));
// 		write(heredoc, "\n", 1);
// 		free(here);
// 	}
// 	close(heredoc);
// 	command->fdread = open(".heredoc.txt", O_RDONLY);
// }