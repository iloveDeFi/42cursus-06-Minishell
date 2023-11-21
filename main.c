#include "minishell.h"

int g_exit_code = 0;

void write_inputrc(void)
{
    int fd;
    char *home;

    home = getenv("HOME");
    home = ft_strjoin(home, "/.inputrc");
    if (home == NULL) {
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
        fprintf(stderr, "CHAOS, there are too many arguments\n"); // TO DO : strerror or perror
        return 1; // Utilisation de 1 pour indiquer une erreur
    }
    // ft_memset(env, 0, sizeof(t_env)); Good ???
    ft_initialize_minishell(&shell, &env);
	ft_initialize_environment(&envList, envp);
    while (1) {
        //signal(SIGINT, handle_signal);
        ft_custom_prompt_msg(&shell);
        char *input = readline("Minis_Hell> ");
        if (shell.av == NULL)
			break ;
        /*
        if (input == NULL) 
        {
            fprintf(stderr, "Exiting...\n"); // TO DO : strerror or perror
            break; // Sortir de la boucle si l'utilisateur a saisi Ctrl+D
        }
        */

        add_history(&shell);

        char *token = ft_strtok(input, " \n");
        int i = 0;
        while (token != NULL) 
        {
            av[i] = malloc(ft_strlen(token) + 1);
            ft_strcpy(av[i], token);
            ft_strtrim_with_quotes(token);
            ft_tokenize_with_quotes(token);
            token = ft_strtok(NULL, " \n");
            i++;
        }
        av[i] = NULL; // La dernière entrée doit être NULL pour indiquer la fin des arguments

        // Créer nouveau processus
        pid_t pid = fork();

        if (pid == -1) 
        {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Dans le processus fils, exécutez la commande
            execvp(av[0], av);
            // Si execvp retourne, il y a eu une erreur
            perror("minishell");
            exit(EXIT_FAILURE);
        } else 
        {
            // Dans le processus parent, attendez que le fils se termine
            wait(NULL);
            int j = 0;
            while (j < i)
                free(av[++j]);
        }
        free(input);
    }
    return 0;
}

/**/