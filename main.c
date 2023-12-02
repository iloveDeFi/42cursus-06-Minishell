#include "minishell.h"

int g_exit_code = 0;

void	exit_shell(t_mini *shell)
{
	if (shell->av)
		free(shell->av);
}

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
    t_mini      shell;
    t_env       *envList = ft_initialize_environment(envp);
    t_env       *env;
    t_commandList commandList;
    t_command   *cmd = NULL;

    (void)av;

    if (ac > 1) 
    {
        fprintf(stderr, "CHAOS, there are too many arguments\n");
        return 1;
    }

    ft_init_commandList(&commandList);
    ft_initialize_minishell(&shell, &env);
    ft_initialize_environment(envp);

    while (1) 
    {
        ft_custom_prompt_msg(&shell);

        if (shell.av == NULL) 
            printf("Arret shell\n");

        ft_manage_history(&shell, shell.av);

        if (ft_check_only_spaces(shell.av) == TRUE) 
        {   
            ft_destroy_current_shell(&shell);
            continue;
        }   
        else if (ft_strcmp(shell.av, "") != 0) 
        {
            if (ft_test_parsing(&commandList, shell.av, &envList)) 
            {
                printf("Test avant EXEC \n");

               if (commandList.head != NULL) 
                {
                    printf("Command to execute: %s\n", commandList.head->name);
                    cmd = commandList.head;

                    if (ft_is_builtins(cmd) == 1)
                    {
                        int status = ft_exec_builtins(cmd, &envList);
                        if (status != 0) 
                            fprintf(stderr, "Error executing builtin command\n");
                    }
                    else
                        printf("Not a builtin, execute external command\n");
                } 
                else 
                    fprintf(stderr, "Error: commandList head is NULL\n");
            }

            ft_destroy_current_shell(&shell);
        }
    }
    ft_exit_shell(&shell);
    return (0);
}
/*
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

*/