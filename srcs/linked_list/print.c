#include "minishell.h"

void ft_print_command(t_command *cmd) 
{
    printf("Command name from print_command : %s\n", cmd->name);

    if (cmd->argCount > 0 && cmd->args != NULL) 
    {
        printf("Arguments:\n");
        for (int i = 0; i < cmd->argCount; i++) 
        {
            printf("%d: %s\n", i + 1, cmd->args[i]);
        }
    }
    else 
    {
        printf("No arguments\n");
    }
}

void ft_print_list(t_commandList *head, void (*printFunction)(t_command *cmd)) 
{
    if (head == NULL || head->head == NULL) 
        return;
    t_command *current = head->head;
    while (current != NULL) 
    {
        printFunction(current);
        current = current->next;
    }
}

// adapt casting depending data type to store in list
void ft_printGeneric(void *data)
{
    char *str = (char *)data;
    printf("%s\n", str);
}

void ft_print_command_list(t_commandList *commandList) 
{
    if (commandList == NULL || commandList->head == NULL) {
        printf("Empty command list\n");
        return;
    }

    printf("Command List is :\n");
    t_command *current = commandList->head;
    while (current != NULL) 
    {
        printf("Name: %s\n", current->name);
        printf("Token Type: %s\n", ft_token_type_to_string(current->tokenType));
        printf("Argument Count: %d\n", current->argCount);
   
        if (current->argCount > 0 && current->args != NULL) {
            printf("print_command_list - Arguments:\n");
            for (int i = 0; i < current->argCount; i++) {
                printf("%d: %s\n", i + 1, current->args[i]);
            }
        } else {
            printf("print_command_list - No arguments\n");
        }
        printf("\n");

        current = current->next;
    }
}

char *ft_token_type_to_string(t_token_type type) {
    switch(type) {
        case PIPE:
            return "PIPE";
        case HEREDOC:
            return "HEREDOC";
        case LPR:
            return "LPR";
        case RPR:
            return "RPR";
        case AND:
            return "AND";
        case OR:
            return "OR";
        case APPEND:
            return "APPEND";
        case OUT:
            return "OUT";
        case IN:
            return "IN";
        case NOT:
            return "NOT";
        case END:
            return "END";
        case COMMAND_TYPE:
            return "COMMAND_TYPE";
        case ARGUMENT_TYPE:
            return "ARGUMENT_TYPE";
        case OPTION_TYPE:
            return "OPTION_TYPE";
        case UNKNOWN_TYPE:
            return "UNKNOWN_TYPE";
        default:
            return "Invalid type";
    }
}

void ft_print_string_array(char **args) 
{
    if (args == NULL) 
    {
        printf("Args array is NULL\n");
        return;
    }
    printf("Arguments are :\n");
    int i = 0;
    while (args[i] != NULL) {
        printf("%s\n", args[i]);
        i++;
    }
}
