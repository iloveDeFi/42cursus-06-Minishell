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


void ft_append_to_commandList_(t_commandList *commandList, t_command *command)
{
    t_command *current;
    
    if (commandList->head == NULL)
    {
        commandList->head = command;
        return;
    }
    current = commandList->head;
    while(current->next != NULL)
    {
        current = current->next;
    }
    current->next = command;
}

void ft_process_tokens(t_commandList *commandList, char **tokens)
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
            ft_append_to_commandList_(commandList, ft_create_new_command(tokens, arg_len)) ;
            tokens += arg_len + 1;
            arg_len = 0;
            tokenIndex = 0;
            continue;
        }
        tokenIndex++;
        arg_len++;
    }

    printf("commandList->head->name = %s\n", commandList->head->args[1]);



}


int ft_launch_parsing_and_execution(char *input, t_env *envList, char **envp) 
{
    t_commandList commandList;


    char **tokens;

    tokens = ft_tokenize_input_with_strtok(input);
    ft_initialize_commandList(&commandList);
    ft_process_tokens(&commandList, tokens);

    if()

    return 0;

    // t_command *command;
    // int j;

    // command = NULL;
	// if (commandList == NULL || input == NULL) {
    //     perror("Error: Invalid pointer to commandList or null input in ft_launch_parsing_and_execution()\n");
    //     return 1;
    // }
    // ft_initialize_commandList(commandList);
	// // TO DO : custom error manager
	// // ft_launch_error_manager(commandList, command, input, envList);

	// if (ft_tokenize_input_with_strtok(commandList, input) >= 1)
	// {
	// 	command = commandList->head;
	// 	command->number_of_pipes = ft_count_number_of_pipes(input);
	// 	while (command != NULL)
	// 	{
	// 		// ft_launch_pipe_execution(command);
    //         printf("-- %s\n", command->name);
    //         j = 0;
    //         while(command->args[j] != NULL)
    //         {
    //             printf("---- %s\n", command->args[j]);
    //             j++;
    //         }
	// 		//ft_launch_redirection_execution(command);
	// 		ft_launch_command_execution(command, commandList, envList, envp);
	// 		command = command->next;
	// 	}

	//  	ft_destroy_commandList(commandList);
	// }
	// else
	// 	perror("Hey, no token from input with strtok in ft_launch_parsing_and_execution.\n");
	// return 0;
}
