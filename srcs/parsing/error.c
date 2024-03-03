#include "minishell.h"

// Gestion des erreurs : Dans vos fonctions de gestion des erreurs, telle que ft_handle_pipes_execution,
// ft_execute_single_command, et ft_handle_redirection_execution, vous pourriez ajouter une gestion plus
// détaillée des erreurs. Actuellement, vous utilisez perror dans certaines parties du code,
//  mais vous pourriez remplacer cela par des appels à ft_handle_error pour une gestion centralisée des erreurs.

// Gestion des erreurs : Vous avez mentionné TO DO : ft_handle_error(), mais dans le code actuel,
// vous utilisez principalement perror pour afficher les messages d'erreur. Vous pourriez vouloir
// remplacer les perror par des appels à ft_handle_error pour centraliser
// la gestion des erreurs dans une fonction dédiée.

// void ft_handle_error(const char *error_message, t_mini *shell)
// {
//     perror(error_message);

//     if (shell != NULL)
//     {
//         if (shell->error != NULL)
//         {
//             // Ajoutez l'erreur à la liste des erreurs dans la structure shell
//             t_error *new_error = (t_error *)malloc(sizeof(t_error));
//             if (new_error != NULL)
//             {
//                 new_error->error = TRUE;
//                 new_error->error_name = ft_custom_strdup(error_message);
//                 new_error->prev = NULL;
//                 new_error->next = shell->error;
//                 if (shell->error->next != NULL)
//                     shell->error->next->prev = new_error;
//                 shell->error->next = new_error;
//             }
//             else
//             {
//                 perror("Error: Memory allocation failure in ft_handle_error()\n");
//                 // Gérez la situation de mémoire insuffisante, peut-être exit(EXIT_FAILURE);
//             }
//         }
//         else
//         {
//             perror("Error: Invalid pointer to error list in ft_handle_error()\n");
//             // Gérez la situation d'erreur, peut-être exit(EXIT_FAILURE);
//         }
//     }
//     else
//     {
//         perror("Error: Invalid pointer to shell in ft_handle_error()\n");
//         // Gérez la situation d'erreur, peut-être exit(EXIT_FAILURE);
//     }
// }

// Return 0 if file exists and user has access rights ; 1 otherwise
int ft_check_if_file_exists(const char *filename)
{
    return access(filename, F_OK) != -1;
}

int	ft_check_if_its_any_white_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\r'
        || c == '\n' || c == '\v' || c == '\f')
        return (1);
    return (0);
}

bool ft_check_if_only_spaces(const char *str)
{
    if (str == NULL)
        return false;
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] != ' ')
            return false;
        i++;
    }
    return true;
}

void ft_initialization_of_errors(t_mini *shell)
{
    if (shell != NULL) {
        shell->error = malloc(sizeof(t_error));
        if (shell->error != NULL) {
            shell->error->error = false;
            shell->error->error_name = NULL;
            shell->error->next = NULL;
            shell->error->prev = NULL;
        }
    }
}

void ft_add_space_around_redirection(char *input)
{
    char *src;
    char modifiedInput[2000];
    char *dest;

    src = input;
    dest = modifiedInput;
    while (*src != '\0')
    {
        if ((*src == '>' || *src == '<') && *(src + 1) != *src)
        {
            *dest++ = ' ';  // Ajouter un espace avant l'opérateur
            *dest++ = *src; // Copier l'opérateur
            *dest++ = ' ';  // Ajouter un espace après l'opérateur
        } else
        {
            *dest++ = *src; // Copier le caractère actuel
        }
        src++;
    }

    *dest = '\0';  // Ajouter le caractère de fin de chaîne
    ft_strcpy(input, modifiedInput);
}
