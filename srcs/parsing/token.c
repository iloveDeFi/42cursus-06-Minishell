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
    token = ft_strtok(inputCopy, " | < << > >>\"\'");
    while (token != NULL) 
    {
        currentCommand = ft_process_token(commandList, currentCommand, token);
        token = ft_strtok(NULL, " | < << > >>\"\'");
        //tokenIndex++;
        /* while (*ptr && (isspace(*ptr) || *ptr == '|' || *ptr == '<' || *ptr == '>'))
            ptr++; 
        token = ft_strtok(ptr, " | < << > >>"); */
    } 
    return commandList->length;
}

void ft_remove_quotes(char *str) 
{
    char *src;
    char *dst;

    src = str;
    dst = str;
    while (*src) 
    {
        if (*src != '\'' && *src != '"') 
            *dst++ = *src;
        src++;
    }
    *dst = '\0';
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
