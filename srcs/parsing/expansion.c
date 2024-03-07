#include "minishell.h"

static char	*ft_get_env_value(char *name, t_env *envList)
{
	t_env	*current;

	current = envList;
	while (current != NULL)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (ft_strdup(""));
}

char	*ft_remove_leading_spaces(char *input)
{
	char	*current;
	char	*result;

	if (input == NULL)
		return (NULL);
	current = input;
	while (*current != '\0' && ft_isspace(*current))
		current++;
	result = strdup(current);
	if (result == NULL)
	{
		perror("Erreur d'allocation mémoire");
		exit(EXIT_FAILURE);
	}
	return (result);
}

static void	manage_in_quote(t_token *token, t_env *envList)
{
	char	**splited;
	int		i;
	char	*tmp;
	char	*tmp_bis;

	if (token->is_in_quote != '"')
		return ;
	splited = ft_split(token->word, ' ');
	i = 0;
	free(token->word);
	token->word = ft_strdup("");
	while (splited[i])
	{
		if (splited[i][0] == '$')
		{
			tmp = ft_get_env_value(splited[i] +1, envList);
			free(splited[i]);
			splited[i] = tmp;
		}
		tmp = ft_strjoin_sep(token->word, splited[i], ' ');
		free(token->word);
		tmp_bis = ft_remove_leading_spaces(tmp);
		token->word = tmp_bis;
		i++;
	}
}

void	replace_environment_variables(t_token *token, t_env *envList)
{
	char	*tmp;

	if (token->word[1] == '?')
	{
		free(token->word);
		token->word = ft_itoa(g_exit_code);
	}
	else
	{
		tmp = ft_get_env_value(token->word + 1, envList);
		free(token->word);
		token->word = tmp;
	}
}

void	ft_found_and_replace_usd(t_token **tokens, t_env *envList)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->is_in_quote == '\'' || tokens[i]->is_in_quote == '"')
		{
			manage_in_quote(tokens[i++], envList);
			continue ;
		}
		if (tokens[i]->word[0] == '$')
		{
			replace_environment_variables(tokens[i], envList);
		}
		i++;
	}
}
