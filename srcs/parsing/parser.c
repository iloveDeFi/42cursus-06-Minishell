#include "minishell.h"

t_command *    ft_create_new_command(char **tokens, int arg_len)
{
	printf("ft_create_new_command\n");
	t_command *command;
	int i;

	i = 0;
	command = (t_command *)malloc(sizeof(t_command));
	// printf("%s\n", tokens[0]);
	command->name = ft_strdup(tokens[0]);
	command->args = (char **)malloc(sizeof(char *) * (arg_len + 2));
	command->argCount = 0;
	while(i < arg_len + 1)
	{
		command->args[i] = ft_strdup(tokens[i]);
		command->argCount++;
		i++;
	}
	command->args[i] = NULL;
	command->next = NULL;
	command->fdread = 0;
	command->fdwrite = 1;
	command->redirection_info.filename = NULL;
	command->redirection_info.delimiter = NULL;
	command->redirection_info.type = NO_REDIRECTION;
	printf("-- command->redirection_info.type = NO_REDIRECTION : %d\n", command->redirection_info.type);
	// printf("arg_len = %d\n", arg_len);
	// printf("name = %s\n", command->name);
	i = 0;
	// while(command->args[i] != NULL)
	// {
	// 	printf("args = %s\n", command->args[i]);
	// 	i++;
	// }
	printf("argCount = %d\n", command->argCount);
	return command;
}

void ft_append_to_command(t_command **first_command, t_command *new_command)
{
	t_command *current_command;

	current_command = *first_command;
	if (*first_command == NULL)
	{
		*first_command = new_command;
		return;
	}
	while (current_command->next != NULL)
	{
		current_command = current_command->next;
	}
	current_command->next = new_command;
}

void ft_parse_tokens(t_command **first_command, char **tokens)
{
	// dont touch at this function, I will refactor it later
	char *token;
	int arg_len;
	int tokenIndex;

	if (tokens == NULL)
		return;

	arg_len = 0;
	tokenIndex = 0;
	while (tokens[tokenIndex] != NULL)
	{
		token = tokens[tokenIndex];
		// // printf("token = %s\n", token );
		if (tokens[tokenIndex + 1] == NULL)
		{
			ft_append_to_command(first_command, ft_create_new_command(tokens, arg_len));
			tokens += arg_len + 1;
			arg_len = 0;
			tokenIndex = 0;
			continue;
		}
		if (ft_strcmp(tokens[tokenIndex + 1], "|") == 0)
		{
			ft_append_to_command(first_command, ft_create_new_command(tokens, arg_len));
			tokens += arg_len + 2;
			arg_len = 0;
			tokenIndex = 0;
			continue;
		}
		tokenIndex++;
		arg_len++;
	}
}

// ---------------- Parse and launch command/s ----------------

// ? TODO : rename in ft_parsing and create a function ft_execution
int ft_launch_parsing_and_execution(t_mini *shell, char *input, t_env *envList, char **envp)
{
	t_command *first_command = NULL;

	char **tokens;
	int i = 0;

	tokens = ft_tokenize_input_with_strtok(input); // TODO rename this function
	//ft_initialize_commandList(command);
	ft_parse_tokens(&first_command, tokens);
	if (first_command->next == NULL) // There is only one command (-> need to fork)
		ft_execute_single_command(first_command, envp, envList);
	else
	{
		ft_execute_cmds(first_command, envp, envList);
	}

	return 0;
}
