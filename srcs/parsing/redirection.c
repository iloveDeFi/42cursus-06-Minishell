#include "minishell.h"

// TO DO : temp_info to ft_free_redirection_info(&redirection_info);
// TO DO : Vérifier si le fichier existe avant de continuer 
// avec ft_check_if_file_exists
t_redirection_info ft_parse_input_redirection(char *input) 
{
	printf("enter in ft_parse_input_redirection\n");

    t_redirection_info redirection_info;

    if(input != NULL && ft_strcmp(input, "<") == 0)
    {   
        redirection_info.type = INPUT_REDIRECTION;
        return redirection_info;
    }
    redirection_info.type = NO_REDIRECTION;
    return redirection_info;
}

// TO DO : temp_info to ft_free_redirection_info(&redirection_info);
// TO DO : Vérifier si le fichier existe avant de continuer 
// avec ft_check_if_file_exists
t_redirection_info ft_parse_output_redirection(char *input) 
{
	printf("enter in ft_parse_output_redirection\n");

    t_redirection_info redirection_info;

    if(input != NULL && ft_strcmp(input, ">") == 0)
    {   
        redirection_info.type = OUTPUT_REDIRECTION;
        return redirection_info;
    }
    redirection_info.type = NO_REDIRECTION;
    return redirection_info;
}

// TO DO : temp_info to ft_free_redirection_info(&redirection_info);
// TO DO : Vérifier si le fichier existe avant de continuer 
// avec ft_check_if_file_exists
t_redirection_info ft_parse_append_redirection(char *input) 
{    
	printf("enter in ft_parse_append_redirection\n");

    t_redirection_info redirection_info;

    if(input != NULL && ft_strcmp(input, ">>") == 0)
    {   
        redirection_info.type = APPEND_REDIRECTION;
        return redirection_info;
    }
    redirection_info.type = NO_REDIRECTION;
    return redirection_info;
}


// TO DO : temp_info to ft_free_redirection_info(&redirection_info);
// TO DO : Vérifier si le fichier existe avant de continuer 
// avec ft_check_if_file_exists
t_redirection_info ft_parse_here_doc_redirection(char *input) 
{
	printf("enter in ft_parse_here_doc_redirection\n");

    t_redirection_info redirection_info;

    if(input != NULL && ft_strcmp(input, "<<") == 0)
    {   
        redirection_info.type = HERE_DOC_REDIRECTION;
        return redirection_info;
    }
    redirection_info.type = NO_REDIRECTION;
    return redirection_info;
}

// TO DO function below to free properly
// ft_free_redirection_info(&temp_info);

t_redirection_type ft_parse_all_redirection(char *token)
{
    printf("enter in ft_parse_all_redirection\n");

    t_redirection_info temp_info;

    temp_info = ft_parse_output_redirection(token);
    if (temp_info.type != NO_REDIRECTION) return temp_info.type;

    temp_info = ft_parse_append_redirection(token);
    if (temp_info.type != NO_REDIRECTION) return temp_info.type;

    temp_info = ft_parse_input_redirection(token);
    if (temp_info.type != NO_REDIRECTION) return temp_info.type;

    temp_info = ft_parse_here_doc_redirection(token);
    // Ne retournez pas directement ici, mais mettez à jour temp_info.type si nécessaire
    if (temp_info.type != NO_REDIRECTION) return temp_info.type;

    // Si aucune correspondance n'est trouvée, renvoyez une valeur par défaut
    return NO_REDIRECTION;
}

