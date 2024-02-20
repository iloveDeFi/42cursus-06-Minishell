#include "minishell.h"

// Vérifie si un caractère est une quote simple ou double
int is_quote(char c) {
    return (c == '\'' || c == '"');
}

// Fonction pour extraire un seul token tout en prenant en compte les quotes simples
char *extract_single_quote_token(char *input, char **end_ptr) {
    char *token_start = input;
    char *token_end = input;

    // Ignorer les espaces initiaux
    while (*token_start == ' ')
        token_start++;

    // Gestion des quotes simples
    if (*token_start == '\'') {
        token_start++; // Passer la quote initiale
        token_end++;
        while (*token_end != '\0') {
            if (*token_end == '\'') {
                token_end++; // Passer la quote finale
                break;
            }
            token_end++;
        }
    } else {
        // Trouver la fin du token
        while (*token_end != '\0' && *token_end != ' ')
            token_end++;
    }

    *end_ptr = token_end;
    return strndup(token_start, token_end - token_start);
}

// Fonction pour extraire un seul token tout en prenant en compte les quotes doubles et l'expansion des variables d'environnement
char *extract_double_quote_token(char *input, char **end_ptr) {
    char *token_start = input;
    char *token_end = input;

    // Ignorer les espaces initiaux
    while (*token_start == ' ')
        token_start++;

    // Gestion des quotes doubles
    if (*token_start == '"') {
        token_start++; // Passer la quote initiale
        token_end++;
        while (*token_end != '\0') {
            if (*token_end == '"') {
                token_end++; // Passer la quote finale
                break;
            } else if (*token_end == '$' && *(token_end + 1) == '{') {
                // Si on trouve ${, on cherche la fin de la variable
                while (*token_end != '\0' && *token_end != '}')
                    token_end++;
            }
            token_end++;
        }
    } else {
        // Trouver la fin du token
        while (*token_end != '\0' && *token_end != ' ')
            token_end++;
    }

    *end_ptr = token_end;
    return strndup(token_start, token_end - token_start);
}
