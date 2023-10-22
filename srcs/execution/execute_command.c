#include "minishell.h"

void    ft_execute_command(t_command *command)
{
    pid_t   child_pid;
    int     status;

    child_pid = fork();
    if (child_pid < 0)
        perror("[ERROR] : Fork error\n");
    if (child_pid == 0)
    {
        execvp(command->name, command->arguments);
        perror("[ERROR] : Execution command\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(child_pid, &status, 0);
        if (WIFEXITED(status))
        {    
            printf("%d\n", WIFEXITED(status));
        }
    }
}
