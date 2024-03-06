#include "minishell.h"

// void ft_execute_command_with_heredoc(const char *command, const char *heredoc_content) 
// {
// 	pid_t child_pid;
// 	char *const cmd[] = {"/bin/sh", "-c", command, NULL};
//     int pipe_fd[2];
//     if (pipe(pipe_fd) == -1) {
//         perror("Erreur lors de la création du tube");
//         exit(EXIT_FAILURE);
//     }
//     child_pid = fork();
//     if (child_pid == -1) {
//         perror("Erreur lors de la création du processus enfant");
//         exit(EXIT_FAILURE);
//     }
//     if (child_pid == 0) {
//         close(pipe_fd[1]);
//         dup2(pipe_fd[0], STDIN_FILENO);
//         close(pipe_fd[0]);
//         execve("/bin/sh", cmd, NULL);
//         perror("Erreur lors de l'exécution de la commande");
//         exit(EXIT_FAILURE);
//     } else {
//         close(pipe_fd[0]);
//         write(pipe_fd[1], heredoc_content, ft_strlen(heredoc_content));
//         close(pipe_fd[1]);
//         waitpid(child_pid, NULL, 0);
//     }
// }
