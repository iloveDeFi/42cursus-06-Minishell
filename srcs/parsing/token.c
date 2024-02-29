#include "minishell.h"

int ft_tokenize_input_with_strtok(t_commandList *commandList, char *input) 
{
    printf("enter tokenize\n");
    char *token;
    char inputCopy[ft_strlen(input) + 1];
    //int tokenIndex;
    //char *ptr;
    t_command *currentCommand;

    //tokenIndex = 0;
    ft_strcpy(inputCopy, input);
    //ptr = inputCopy;
    currentCommand = NULL;
    token = ft_strtok(inputCopy, " | < << > >>\"");
    while (token != NULL) 
    {
        currentCommand = ft_process_token(commandList, currentCommand, token);
        token = ft_strtok(NULL, " | < << > >>\"");
        //tokenIndex++;
        /* while (*ptr && (isspace(*ptr) || *ptr == '|' || *ptr == '<' || *ptr == '>'))
            ptr++; 
        token = ft_strtok(ptr, " | < << > >>"); */
    } 
    return commandList->length;
}

void ft_remove_quotes(char *input)
{
    int i = 0, j = 0;
    int len = strlen(input);

    // Parcours de la chaîne d'entrée
    for (i = 0; i < len; i++)
    {
        // Si le caractère actuel n'est pas un guillemet, copiez-le dans la nouvelle chaîne
        if (input[i] != '"')
        {
            input[j++] = input[i];
        }
    }
    
    // Ajoutez un caractère nul à la fin de la chaîne modifiée
    input[j] = '\0';
}



bool    ft_check_quotes(char *input) 
{
    int single_quotes = 0;
    int double_quotes = 0;

    while (*input) 
    {
        if (*input == '\'') 
            single_quotes++;
        else if (*input == '"') 
            double_quotes++;
        input++;
    }

    if (single_quotes % 2 == 0 && double_quotes % 2 == 0) 
        return true;
    else 
    {
        g_exit_code = 1;
        return false;
    }
}
