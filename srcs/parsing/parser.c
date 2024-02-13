#include "minishell.h"

void ft_process_the_first_token_as_a_command(t_commandList *commandList, char *token) 
{
	// CHECK LOGIC WITH TOKEN && COMMANDLIST
    t_command *command;

	command = NULL;
	if (!ft_check_if_pipe_in_string(token))
	{
    	command = (t_command *)malloc(sizeof(t_command));

    	if (command == NULL) 
    	{
    	    perror("CHAOS, error allocating memory");
    	    ft_destroy_command(commandList);
    	    exit(EXIT_FAILURE);
    	}

    	ft_init_new_node(commandList, command, token);
		ft_append_to_commandList(commandList, command);

    	printf("Printing commandList at the end of ft_process_the_first_token_as_a_command:\n");
    	ft_print_commandList(commandList);
	}
}

// TO DO HERE : MAYBE t_command *command accessible from commandList directly?
void ft_process_token_as_an_argument(t_commandList *commandList, t_command *command, char *token) 
{
    if (command == NULL || token == NULL) 
    {
        perror("Erreur dans ft_process_token_as_an_argument : mauvaise entrée à traiter\n");
        return;
    }

    char **newArgs = (char **)malloc((command->argCount + 2) * sizeof(char *));
    if (newArgs == NULL) 
    {
        perror("CHAOS, erreur d'allocation mémoire dans ft_process_token_as_an_argument");
        ft_destroy_command(commandList);
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (i < command->argCount) 
    {
        newArgs[i] = command->args[i];
        i++;
    }

    // Ajout du nouveau token en tant que nouvel argument
    newArgs[command->argCount] = ft_strdup(token);
    if (newArgs[command->argCount] == NULL)
    {
        perror("Erreur d'allocation mémoire dans ft_process_token_as_an_argument");
        ft_destroy_command(commandList);
        exit(EXIT_FAILURE);
    }

    // Ajout d'un pointeur NULL à la fin du tableau
    newArgs[command->argCount + 1] = NULL;

    // Libération de la mémoire de l'ancien tableau d'arguments
    free(command->args);

    // Mise à jour du pointeur vers le nouveau tableau d'arguments
    command->args = newArgs;
    command->argCount++;
}


int ft_split_input_in_token_to_commandList(t_commandList *commandList, char *input) 
{
    char *token;
    char inputCopy[ft_strlen(input) + 1];
    int tokenIndex;
    char *delimiters;
    
    tokenIndex = 0;
    delimiters = " ";

    ft_strcpy(inputCopy, input);

    if (ft_check_if_pipe_in_string(inputCopy))
    {
        delimiters = " |";
        token = ft_strtok(inputCopy, delimiters);
		while (token != NULL) 
        {
            // Traiter chaque sous-input
            ft_process_sub_input_as_command(commandList, token);
            token = ft_strtok(NULL, delimiters);
        }
	}
    else    
        token = ft_strtok(inputCopy, delimiters);

    if (token == NULL) 
    {
        perror("An error has occurred during input tokenization: Empty command\n");
        return 1;
    }

    ft_process_the_first_token_as_a_command(commandList, token);
    tokenIndex++;

    while ((token = ft_strtok(NULL, delimiters)) != NULL) 
    {
        if (tokenIndex == 1 && ft_strcmp(commandList->tail->name, "cd") == 0) 
        {
            ft_process_cd_argument(commandList->tail, token);
            break;
        }

        printf("Launch ft_process_token_as_an_argument with argument number %d: named %s\n", tokenIndex, token);
        ft_process_token_as_an_argument(commandList, commandList->tail, token);
        tokenIndex++;
    }

    return commandList->length;
}



int ft_parse_and_add_to_commandList(t_commandList *commandList, char *input) 
{
    if (commandList == NULL)
    {
        perror("commandList head is NULL in ft_parse_and_add_to_commandList");
        return 1;
    }
    if (ft_split_input_in_token_to_commandList(commandList, input) > 0) 
    {
        return 0;
    } 
    else 
    {
        perror("Parsing failed in ft_parse_and_add_to_commandList");
        ft_destroy_command(commandList);
        return 1;
    }
}

int ft_launch_parsing_and_execution(t_commandList *commandList, char *input, t_env *envList, char **envp) 
{
    t_command *command;

    ft_initialize_commandList(commandList);

    if (ft_parse_and_add_to_commandList(commandList, input) == 0 && commandList->head != NULL) 
    {
        ft_print_commandList(commandList);
		
        command = commandList->head;
        if (ft_count_number_of_pipes(input) > 1)
        {
			if (ft_count_number_of_pipes(input) > MAX_COMMANDS)
				perror("Please do not use more than 10 pipes.\n");
            ft_execute_piped_commands(command, (ft_count_number_of_pipes(input) + 1));
        }
        
        else if (ft_execute_single_command(command, commandList, envList, envp) != 0) 
        {
            perror("Error executing command\n");
            ft_destroy_command(commandList);
            return 1;
        }
        return 0;
    } 
    else 
    {
        perror("ft_parse_and_add_to_commandList failed. commandList problem.\n");
        return 1;
    }
}
