#include "minishell.h"

void	ft_init_new_node_name(t_commandList *commandList, \
	t_command *command, char *token)
{
	command->name = ft_strdup(token);
	if (command->name == NULL)
	{
		perror("CHAOS, error allocating memory");
		ft_destroy_commandlist(commandList);
		exit(EXIT_FAILURE);
	}
}

void	ft_init_new_node_args(t_commandList *commandList, \
	t_command *command, char *token)
{
	command->args = (char **)malloc(sizeof(char *) * 2);
	if (command->args == NULL)
	{
		perror("CHAOS, error allocating memory");
		ft_destroy_commandlist(commandList);
		exit(EXIT_FAILURE);
	}
	command->args[0] = ft_strdup(token);
	command->args[1] = NULL;
	if (command->args[0] == NULL)
	{
		free(command->name);
		free(command->args);
		perror("CHAOS, error allocating memory");
		ft_destroy_commandlist(commandList);
		exit(EXIT_FAILURE);
	}
	command->argCount = 1;
}

void	ft_init_new_node_redirection_info(t_command *command)
{
	command->redirection_info.filename = NULL;
	command->redirection_info.delimiter = NULL;
	command->redirection_info.type = NO_REDIRECTION;
}

void	ft_init_new_node(t_commandList *commandList, \
	t_command *command, char *token)
{
    ft_init_new_node_name(commandList, command, token);
    command->data = NULL;
    ft_init_new_node_args(commandList, command, token);
    command->next = NULL;
    command->prev = NULL;
    command->envp = NULL;
    command->envList = NULL;
	// info about pipes
	command->has_pipe = FALSE;
    ft_memset(command->pipes, 0, sizeof(command->pipes));
    ft_memset(command->child_pids, 0, sizeof(command->child_pids));
    command->pipe_index = 0;
    command->number_of_pipes = 0;
	// info about redirection
	command->has_redirection = FALSE;
	command->redirection_info.filename = NULL;
    command->redirection_info.delimiter = NULL;
	ft_init_new_node_redirection_info(command);
}
