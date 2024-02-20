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
    token = ft_strtok(inputCopy, " | < << > >>");
    while (token != NULL) 
    {
        currentCommand = ft_process_token(commandList, currentCommand, token);
        token = ft_strtok(NULL, " | < << > >>");
        //tokenIndex++;
         /* while (*ptr && (isspace(*ptr) || *ptr == '|' || *ptr == '<' || *ptr == '>'))
            ptr++; 
        token = ft_strtok(ptr, " | < << > >>");*/
    } 
    return commandList->length;
}
