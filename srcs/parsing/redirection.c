#include "minishell.h"

t_redirection_info ft_parse_input_redirection(char *input) 
{
	char *input_sign;
	size_t len;
    t_redirection_info redirection_info;
    redirection_info.filename = NULL;
    redirection_info.delimiter = NULL;
    redirection_info.type = INPUT_REDIRECTION;

    input_sign = ft_strstr(input, "<");
    if (input_sign != NULL) {
        input_sign++; // Avance au-delà de "<"
        while (*input_sign == ' ')
            input_sign++;
        redirection_info.filename = ft_strdup(input_sign);

        if (redirection_info.filename != NULL) {
            len = ft_strlen(redirection_info.filename);
            while (len > 0 && redirection_info.filename[len - 1] == ' ')
                redirection_info.filename[--len] = '\0';
        } else {
            perror("Erreur d'allocation mémoire pour le nom du fichier cible de la redirection d'entrée");
            exit(EXIT_FAILURE);
        }
    }
    return redirection_info;
}

// TO DO CHECK FREE AVEC STRDUP
t_redirection_info ft_parse_output_redirection(char *input) 
{    
	char *output_sign;
	size_t len;
	t_redirection_info redirection_info;
    redirection_info.filename = NULL;
    redirection_info.delimiter = NULL;
    redirection_info.type = OUTPUT_REDIRECTION;
    output_sign = ft_strstr(input, ">");
    if (output_sign != NULL) {
        output_sign++;
        while (*output_sign == ' ')
            output_sign++;
        redirection_info.filename = ft_strdup(output_sign);
        len = 0;
        if (redirection_info.filename != NULL) {
            len = ft_strlen(redirection_info.filename);
            while (len > 0 && redirection_info.filename[len - 1] == ' ')
                redirection_info.filename[--len] = '\0';
        }
        if (redirection_info.filename == NULL) {
            perror("Erreur d'allocation mémoire pour le nom du fichier cible");
            exit(EXIT_FAILURE);
        }
    }
    return redirection_info;
}

t_redirection_info ft_parse_append_redirection(char *input) 
{    
	char *append_sign;
	size_t len;
	t_redirection_info redirection_info;
    redirection_info.filename = NULL;
    redirection_info.delimiter = NULL;
    redirection_info.type = APPEND_REDIRECTION;

    append_sign = ft_strstr(input, ">>");
    if (append_sign != NULL) {
        append_sign += 2; // Avance au-delà de ">>"
        while (*append_sign == ' ')
            append_sign++;
        redirection_info.filename = ft_strdup(append_sign);

        if (redirection_info.filename != NULL) {
            len = ft_strlen(redirection_info.filename);
            while (len > 0 && redirection_info.filename[len - 1] == ' ')
                redirection_info.filename[--len] = '\0';
        } else {
            perror("Erreur d'allocation mémoire pour le nom du fichier cible de la redirection d'ajout");
            exit(EXIT_FAILURE);
        }
    }
    return redirection_info;
}

t_redirection_info ft_parse_here_doc_redirection(char *input) {
	char *heredoc_sign;
	size_t len;
    t_redirection_info redirection_info;
    redirection_info.filename = NULL;
    redirection_info.delimiter = NULL;
    redirection_info.type = HERE_DOC_REDIRECTION;

    heredoc_sign = ft_strstr(input, "<<");
    if (heredoc_sign != NULL) {
        heredoc_sign += 2; // Avance au-delà de "<<"
        while (*heredoc_sign == ' ')
            heredoc_sign++;
        redirection_info.delimiter = ft_strdup(heredoc_sign);

        if (redirection_info.delimiter != NULL) {
            len = ft_strlen(redirection_info.delimiter);
            while (len > 0 && redirection_info.delimiter[len - 1] == ' ')
                redirection_info.delimiter[--len] = '\0';
        } else {
            perror("Erreur d'allocation mémoire pour le délimiteur du here-document");
            exit(EXIT_FAILURE);
        }
    }
    return redirection_info;
}

t_redirection_info ft_parse_all_redirection(char *input)
{
	t_redirection_info redirection_info;
	t_redirection_info temp_info;

	redirection_info.type = NO_REDIRECTION;

	temp_info = ft_parse_output_redirection(input);
	if (temp_info.type != NO_REDIRECTION) {
		redirection_info = temp_info;
	}

	temp_info = ft_parse_append_redirection(input);
	if (temp_info.type != NO_REDIRECTION) {
		redirection_info = temp_info;
	}

	temp_info = ft_parse_input_redirection(input);
	if (temp_info.type != NO_REDIRECTION) {
		redirection_info = temp_info;
	}

	temp_info = ft_parse_here_doc_redirection(input);
	if (temp_info.type != NO_REDIRECTION) {
		redirection_info = temp_info;
	}

	return redirection_info;
}
