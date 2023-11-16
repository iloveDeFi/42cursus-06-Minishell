#include "minishell.h"

int g_exit_code = 0;

void write_inputrc(void)
{
    int fd;
    //char *buf;
    char *home;

    home = getenv("HOME");
    home = ft_strjoin(home, "/.inputrc");
    if (home == NULL) 
    {
        perror("ft_strjoin");
        exit(EXIT_FAILURE);
    }

    fd = open(home, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) 
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    const char *content = "set echo-control-characters Off\n";
    ssize_t bytes_written = write(fd, content, strlen(content));
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        free(home);
        exit(EXIT_FAILURE);
    }
    close(fd);
    free(home);
}


int main(int ac, char **av, char **envp) 
{
	t_mini	shell;
	t_envList	envList;
	t_env	*env;

    if (ac > 1) 
    {
        fprintf(stderr, "CHAOS, too many arguments\n");
        return 1;
    }
	ft_initialize_minishell(&shell, &env);
	ft_initialize_environment(&envList, envp);
    while (1) 
	{
		// run function signal(SIGINT, handle_signal);
		ft_custom_prompt_msg(&shell);
        char *input = readline("Minis_Hell> ");

        if (input == NULL) 
        {
            fprintf(stderr, "Exiting...\n");
            break;
        }

        add_history(input);

        char *token = ft_strtok(input, " \n");
        int i = 0;
        while (token != NULL) 
        {
            av[i] = malloc(ft_strlen(token + 1));
            ft_strcpy(av[i], token);
            ft_strtrim_with_quotes(token);
            ft_tokenize_with_quotes(token);
            token = ft_strtok(NULL, " \n");
            i++;
        }
        av[i] = NULL;

        pid_t pid = fork();
        // libérer la mémoire allouée avant exit(EXIT_FAILURE) 
        // dans le processus enfant pour éviter les fuites de mémoire.
        if (pid == -1) 
        {
            perror("fork");
            exit(EXIT_FAILURE);
        } 
        else if (pid == 0) 
        {
            execvp(av[0], av);
            perror("minishell");
            exit(EXIT_FAILURE);
        } else
            {
                wait(NULL);
                int j = 0;
                while (j < i)
                    free(av[++j]);
            }
        free(input);
    }
    return 0;
}
