#include "minishell.h"

// TO DO : temp_info to ft_free_redirection_info(&redirection_info);
// Vérifier si le fichier existe avant de continuer ft_check_if_file_exists
t_redirection_info ft_parse_input_redirection(char *input) 
{
    printf("enter in ft_parse_input_redirection\n");
    char *input_sign;
    size_t len;
    t_redirection_info redirection_info;
   
    redirection_info.type = INPUT_REDIRECTION;
    input_sign = ft_strstr(input, "<");
    if (input_sign != NULL) {
        input_sign++; // Passer après "<"
        while (*input_sign == ' ')
            input_sign++;
        redirection_info.filename = ft_strdup(input_sign);

        if (redirection_info.filename != NULL) {
            len = strlen(redirection_info.filename);
            while (len > 0 && redirection_info.filename[len - 1] == ' ')
                redirection_info.filename[--len] = '\0';
			
            // Vérifier si le fichier existe avant de continuer
            if (!ft_check_if_file_exists(redirection_info.filename)) {
                fprintf(stderr, "Error: The file %s does not exist.\n", redirection_info.filename);
                free(redirection_info.filename); // Libérer la mémoire allouée pour filename
                exit(EXIT_FAILURE);
            }	
        } else {
            perror("Erreur d'allocation mémoire pour le nom du fichier cible de la redirection d'entrée");
            exit(EXIT_FAILURE);
        }
    } else {
        // Si aucune redirection d'entrée n'est trouvée, initialiser filename à NULL
        redirection_info.filename = NULL;
    }

    printf("redirection_info (input redirection): type = %d, filename = %s\n", redirection_info.type, redirection_info.filename != NULL ? redirection_info.filename : "(null)");
    return redirection_info;
}

// TO DO : temp_info to ft_free_redirection_info(&redirection_info);
// Vérifier si le fichier existe avant de continuer ft_check_if_file_exists
t_redirection_info ft_parse_output_redirection(char *input) 
{
    printf("enter in ft_parse_output_redirection\n");    
    char *output_sign;
    size_t len;
    t_redirection_info redirection_info;

    redirection_info.type = OUTPUT_REDIRECTION;
    output_sign = ft_strstr(input, ">");
    if (output_sign != NULL) {
        output_sign++;
        while (*output_sign == ' ')
            output_sign++;
        redirection_info.filename = ft_strdup(output_sign);
        
        if (redirection_info.filename != NULL) {
            len = strlen(redirection_info.filename);
            while (len > 0 && redirection_info.filename[len - 1] == ' ')
                redirection_info.filename[--len] = '\0';
        } else {
            perror("Erreur d'allocation mémoire pour le nom du fichier cible");
            exit(EXIT_FAILURE);
        }
    } else {
        // Si aucune redirection de sortie n'est trouvée, initialiser filename à NULL
        redirection_info.filename = NULL;
    }
    
    //printf("redirection_info (output redirection): type = %d, filename = %s\n", redirection_info.type, redirection_info.filename != NULL ? redirection_info.filename : "(null)");
    return redirection_info;
}


// TO DO : temp_info to ft_free_redirection_info(&redirection_info);
// Vérifier si le fichier existe avant de continuer ft_check_if_file_exists
t_redirection_info ft_parse_append_redirection(char *input) 
{    
    printf("enter in ft_parse_append_redirection\n");
    char *append_sign;
    size_t len;
    t_redirection_info redirection_info;

    redirection_info.type = APPEND_REDIRECTION;
    append_sign = ft_strstr(input, ">>");
    if (append_sign != NULL) {
        append_sign += 2; // Avance au-delà de ">>"
        while (*append_sign == ' ')
            append_sign++;
        redirection_info.filename = ft_strdup(append_sign);

        if (redirection_info.filename != NULL) {
            len = strlen(redirection_info.filename);
            while (len > 0 && redirection_info.filename[len - 1] == ' ')
                redirection_info.filename[--len] = '\0';
        } else {
            perror("Erreur d'allocation mémoire pour le nom du fichier cible de la redirection d'ajout");
            exit(EXIT_FAILURE);
        }
    } else {
        // Si aucune redirection d'ajout n'est trouvée, initialiser filename à NULL
        redirection_info.filename = NULL;
    }
   //printf("redirection_info (append redirection): type = %d, filename = %s\n", redirection_info.type, redirection_info.filename != NULL ? redirection_info.filename : "(null)");
    return redirection_info;
}


// TO DO : free delimiteur
// TO DO : strdup where is free
// TO DO : temp_info to ft_free_redirection_info(&redirection_info);
t_redirection_info ft_parse_here_doc_redirection(char *input) 
{
    printf("enter in ft_parse_here_doc_redirection\n");
    char *heredoc_sign;
    size_t len;
    t_redirection_info redirection_info;

    redirection_info.type = HERE_DOC_REDIRECTION;
    heredoc_sign = ft_strstr(input, "<<");
    if (heredoc_sign != NULL) {
        heredoc_sign += 2;
        while (*heredoc_sign == ' ')
            heredoc_sign++;
        redirection_info.delimiter = ft_strdup(heredoc_sign);

        if (redirection_info.delimiter != NULL) {
            len = strlen(redirection_info.delimiter);
            while (len > 0 && redirection_info.delimiter[len - 1] == ' ')
                redirection_info.delimiter[--len] = '\0';
        } else {
            perror("Erreur d'allocation mémoire pour le délimiteur du here-document");
            exit(EXIT_FAILURE);
        }
    } else {
        // Si aucun here-document n'est trouvé, initialiser delimiter à NULL
        redirection_info.delimiter = NULL;
    }
    //printf("redirection_info (heredoc redirection): type = %d, filename = %s\n", redirection_info.type, redirection_info.filename != NULL ? redirection_info.filename : "(null)");
    return redirection_info;
}


t_redirection_info ft_parse_all_redirection(t_command *command)
{
    printf("enter in ft_parse_all_redirection\n");

    t_redirection_info temp_info;
    t_redirection_info final_info;

    temp_info = ft_parse_output_redirection(command->name);
    if (temp_info.type != NO_REDIRECTION) {
        final_info = temp_info;
    }

    temp_info = ft_parse_append_redirection(command->name);
    if (temp_info.type != NO_REDIRECTION) {
        final_info = temp_info;
    }

    temp_info = ft_parse_input_redirection(command->name);
    if (temp_info.type != NO_REDIRECTION) {
        final_info = temp_info;
    }

    temp_info = ft_parse_here_doc_redirection(command->name);
    if (temp_info.type != NO_REDIRECTION) {
        final_info = temp_info;
    }

    // Libération de la mémoire précédemment allouée pour redirection_info
    free(command->redirection_info.filename);
    free(command->redirection_info.delimiter);

    // Affectation des nouvelles valeurs à redirection_info
    command->redirection_info = final_info;
    //printf("final_info: type = %d, filename = %s, delimiter = %s\n", final_info.type, final_info.filename, final_info.delimiter);

    return final_info;
}

