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

// int ft_parse_all_redirection(char *token)
// {
//     printf("enter in ft_parse_all_redirection\n");

//     t_redirection_info temp_info;

//     temp_info = ft_parse_output_redirection(token);
//     if (temp_info.type != NO_REDIRECTION)
//         return temp_info.type;

//     temp_info = ft_parse_append_redirection(token);
//     if (temp_info.type != NO_REDIRECTION)
//         return temp_info.type;

//     temp_info = ft_parse_input_redirection(token);
//     if (temp_info.type != NO_REDIRECTION)
//         return temp_info.type;

//     temp_info = ft_parse_here_doc_redirection(token);
//     // Ne retournez pas directement ici, mais mettez à jour temp_info.type si nécessaire
//     if (temp_info.type != NO_REDIRECTION)
//         return temp_info.type;

//     // Si aucune correspondance n'est trouvée, renvoyez une valeur par défaut
//     return 0;
// }

// int ft_tokenize_redirection(char *tokens)
// {
//     printf("enter in ft_tokenize_redirection\n");

//     if(ft_strcmp(tokens, "<") == 0 || ft_strcmp(tokens, "<<") == 0 || ft_strcmp(tokens, ">") == 0 || ft_strcmp(tokens, ">>"))
//         return 0;
//     return 1;
// }

void	r_left(t_command *new, char *token, char **tokens, char **tok)
{
	printf("enter in r_left\n");
    char	*file;

	file = get_filename(new, tokens, tok);
    printf("file = %s\n", file);
	if (!file)
	{
		fprintf(stderr, "Missing filename for redirection.\n");
		g_exit_code = 1;
		return;
	}
	new->fdread = open(file, O_RDONLY);
	if (new->fdread == -1)
	{
		perror("issue open r_left");
		g_exit_code = 1;
	}
	free(file);
}

char	*get_filename(t_command *new, char **tokens, char **tok)
{
	printf("enter in get_filename\n");
    int		j;
	char	*filename;

	j = 0;
	while (*tokens[j])
	{
		if (*tokens[j] == '<')
			break;
		j++;
	}
	if (*tokens[j] == '\0')
	{
		fprintf(stderr, "Invalid redirection token.\n");
		return (NULL);
	}
	j++;
	while (isspace(*tokens[j]))
		j++;
	if (tokens[j] == '\0')
	{
		fprintf(stderr, "Missing filename for redirection.\n");
		return (NULL);
	}
	printf("filename = %s\n", *tok);
    filename = ft_strdup(*tok);
    printf("filename = %s\n", filename);
	if (!filename)
		perror("issue malloc get_filename");
	return (filename);
}
