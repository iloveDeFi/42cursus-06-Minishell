#include "minishell.h"

t_command *    ft_create_new_command(char **tokens, int arg_len)
{
    t_command *command;
    int i;

    i = 0;
    command = (t_command *)malloc(sizeof(t_command));
    printf("%s\n", tokens[0]);
    command->name = ft_strdup(tokens[0]);
    command->args = (char **)malloc(sizeof(char *) * (arg_len + 2));
    while(i < arg_len + 1)
    {
        command->args[i] = ft_strdup(tokens[i]);
        command->argCount++;
        i++;
    }
    command->args[i] = NULL;
    printf("arg_len = %d\n", arg_len);
    printf("name = %s\n", command->name);
    i = 0;
    while(command->args[i] != NULL)
    {
        printf("args = %s\n", command->args[i]);
        i++;
    }
    return command;
}

void ft_append_to_command(t_command **first_command, t_command *new_command)
{
    t_command *current_command;

    current_command = *first_command;
    if (*first_command == NULL)
    {
        *first_command = new_command;
        printf("1 %s\n", (*first_command)->name);
        return;
    }
    while (current_command->next != NULL)
    {
        current_command = current_command->next;
    }
    current_command->next = new_command;
}

void ft_process_tokens(t_command **command, char **tokens)
{
    char *token;
    int arg_len;
    int tokenIndex;

    arg_len = 0;
    tokenIndex = 0;
    while (tokens[tokenIndex] != NULL)
    {
        token = tokens[tokenIndex];
        printf("token = %s\n", token );
        if (ft_strcmp(token, "|") == 0 || tokens[tokenIndex+1] == NULL)
        {
            ft_append_to_command(command, ft_create_new_command(tokens, arg_len));
            tokens += arg_len + 1;
            arg_len = 0;
            tokenIndex = 0;
            continue;
        }
        tokenIndex++;
        arg_len++;
    }
}


int ft_launch_parsing_and_execution(char *input, t_env *envList, char **envp) 
{
    t_command *first_command = NULL;

    char **tokens;

    tokens = ft_tokenize_input_with_strtok(input);
    //ft_initialize_commandList(command);
    ft_process_tokens(&first_command, tokens);
    if (first_command->next != NULL)
    {
        printf("first_command->name = %s\n", first_command->name);
        exec_cmd(first_command, envList);
    }
        
    return 0;
}

//int	ft_launch_parsing_and_execution(t_commandList *commandList, \
	char *input, t_env *envList, char **envp)
// {
// 	t_command	*command;

//     command = NULL;
// 	if (commandList == NULL || input == NULL) {
//         perror("Error: Invalid pointer to commandList or null input in ft_launch_parsing_and_execution()\n");
//         return 1;
//     }
//     ft_initialize_commandList(commandList);
// 	if (!ft_check_quotes(input))
// 	{
// 		printf(">\n");
// 		return 0;
// 	}
// 	ft_remove_quotes(input);
// 	if (ft_tokenize_input_with_strtok(commandList, input) >= 1)
// 	{
// 		command = commandList->head;
// 		while (command != NULL)
// 		{
// 			ft_launch_redirection_execution(command);
// 			ft_launch_command_execution(command, commandList, envList, envp);
// 			command = command->next;
// 		}

// 	 	ft_destroy_commandList(commandList);
// 	}
// 	else
// 		perror("Hey, no token from input with strtok in ft_launch_parsing_and_execution.\n");
// 	return 0;
// }
