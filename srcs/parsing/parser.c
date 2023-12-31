
#include "minishell.h"

/*int ft_split_arg(t_argList *argList, char *input)
{
    char *token;
    
    token = ft_strtok(input, " ");
    while (token != NULL)
    {
        t_arg *newArg = malloc(sizeof(t_arg));
        if (newArg == NULL)
        {
            perror("CHAOS, error allocating memory");
            exit(EXIT_FAILURE);
        }
        newArg->name = ft_strdup(token);
        if (argList->head == NULL)
        {
            argList->head = newArg;
            argList->tail = newArg;
            newArg->prev = NULL; 
        }
        else {
            newArg->prev = argList->tail;
            //argList->tail->next = newArg;
            argList->tail = newArg;
        }
        argList->arglistLength++;
        token = strtok(NULL, " ");
    }
    return argList->arglistLength;
}*/

int ft_split_arg(t_list *argList, char *input)
{
    char *token;
    
    token = ft_strtok(input, " ");
    while (token != NULL)
    {
        t_arg *newArg = malloc(sizeof(t_arg));
        if (newArg == NULL)
        {
            perror("CHAOS, error allocating memory");
            exit(EXIT_FAILURE);
        }
        newArg->name = ft_strdup(token);

        if (argList->head == NULL)
        {
            argList->head = ft_createNode(newArg);
            argList->tail = argList->head;
        }
        else 
        {
            appendToList(&(argList->head), ft_createNode(newArg));
            argList->tail = argList->tail->next;
        }

        argList->length++;
        token = strtok(NULL, " ");
    }

    return argList->length;
}

/*char *ft_find_envVar(t_envVar *head, const char *targetName)
{
    t_envVar *current = head;
    while (current != NULL)
    {
        if (ft_strcmp(current->name, targetName) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}*/

t_envVar *ft_find_envVar(t_envVar *head, const char *targetName)
{
    t_envVar *current = head;
    while (current != NULL)
    {
        if (ft_strcmp(current->name, targetName) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}
