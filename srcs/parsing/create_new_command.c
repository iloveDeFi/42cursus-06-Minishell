/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelda <jbelda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:48:05 by jbelda            #+#    #+#             */
/*   Updated: 2024/03/07 18:48:06 by jbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_initialize_command_data(t_command *command, \
	char *name, int arg_len)
{
	command->name = ft_strdup(name);
	command->args = (char **)malloc(sizeof(char *) * (arg_len + 2));
	command->argcount = 0;
}

static void	ft_finalize_command_creation(t_command *command, \
	int args_index, int fdwrite, int fdread)
{
	command->argcount = args_index;
	command->args[args_index] = NULL;
	command->next = NULL;
	command->fdread = fdread;
	command->fdwrite = fdwrite;
}

static t_command	*ft_create_new_command(t_token **tokens, \
	int arg_len, int fdwrite, int fdread)
{
	t_command	*command;
	int			token_index;
	int			args_index;

	token_index = 0;
	args_index = 0;
	command = (t_command *)malloc(sizeof(t_command));
	if (ft_is_redirection(tokens[token_index]->word))
		token_index += 2;
	ft_initialize_command_data(command, tokens[token_index]->word, arg_len);
	while (token_index < arg_len + 1)
	{
		if (ft_is_redirection(tokens[token_index]->word))
		{
			token_index += 2;
			continue ;
		}
		command->args[args_index] = ft_strdup(tokens[token_index]->word);
		args_index++;
		token_index++;
	}
	ft_finalize_command_creation(command, args_index, fdwrite, fdread);
	return (command);
}

bool	ft_parse_tokens_loop(t_command **commands, t_token **tokens, \
int *tokenindex, int *fdreadwrite)
{
	while (tokens[*tokenindex] != NULL)
	{
		if (ft_is_redirection(tokens[*tokenindex]->word))
		{
			if (ft_parse_all_redirection(tokens[*tokenindex]->word, \
				tokens[*tokenindex + 1]->word, &fdreadwrite[1], \
				&fdreadwrite[0]) == false)
				return (false);
		}
		else if (tokens[*tokenindex + 1] == NULL || \
			ft_strcmp(tokens[*tokenindex + 1]->word, "|") == 0)
		{
			ft_command_add_back(commands, ft_create_new_command(tokens, \
				*tokenindex, fdreadwrite[0], fdreadwrite[1]));
			tokens += *tokenindex + 1 + (tokens[*tokenindex + 1] != NULL);
			*tokenindex = -1;
			fdreadwrite[0] = 1;
			fdreadwrite[1] = 0;
		}
		else if (ft_strcmp(tokens[*tokenindex + 1]->word, "<<") == 0)
			ft_command_add_back(commands, ft_create_new_command(tokens, \
				*tokenindex, fdreadwrite[0], fdreadwrite[1]));
		(*tokenindex)++;
	}
	return (true);
}

// 0: fdread, 1: fdwrite
bool	ft_parse_tokens(t_command **commands, t_token **tokens)
{
	int	tokenindex;
	int	fdreadwrite[2];

	tokenindex = 0;
	fdreadwrite[0] = 0;
	fdreadwrite[1] = 1;
	return (ft_parse_tokens_loop(commands, tokens, &tokenindex, fdreadwrite));
}
