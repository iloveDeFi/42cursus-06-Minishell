#include "minishell.h"

/* returns true if input is a space, false otherwise */
int    ft_isaspace(char c)
{
    if (c == ' ' || c == '\t')
        return (1);
    return (0);
}

/* returns the index after it has eliminated the spaces */
void    space_index(t_command *command, char *input)
{
    while (input[command->i] && ft_isaspace(input[command->i]))
        command->i++;
}

/* returns true if char is a delimiter
    if flag == s takes into account the spaces */
int    isdeli(char c, char flag)
{
    if (c == '|' || c == '<' || c == '>')
        return (1);
    if (flag == 's' && ft_isaspace(c))
        return (1);
    return (0);
}

/* returns the length of the next word to be malloc*/
int    word_len(char *input, int i)
{
    int    len;

    len = 0;
    while (input[i] && !isdeli(input[i], '!'))
    {
        len++;
        i++;
    }
    return (len + 1);
}

/* gets the next word (probably the filename) until | or redirection */
char    *get_filename(t_command *command, char *input)
{
    int        j;
    char    *filename;

    space_index(command, input);
    j = -1;
    if (input[command->i] == '\0')
        return (NULL);
    filename = malloc(sizeof(char) * word_len(input, command->i));
    if (!filename)
        perror("issue malloc get_filename");
    while (input[command->i] && !ft_isaspace(input[command->i]))
    {
        filename[++j] = input[command->i];
        command->i++;
    }
    filename[++j] = '\0';
    return (filename);
}