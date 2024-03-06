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

static void	manage_in_quote(t_token *token, t_env *envList)
{
	char	**splited;
	int		i;
	char	*tmp;

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
			tmp = ft_get_env_value(splited[i]+1, envList);
			free(splited[i]);
			splited[i] = tmp;

		}
		tmp = ft_strjoin_sep(token->word, splited[i], ' ');
		free(token->word);
		token->word = tmp;
		i++;
	}
}

void	ft_found_and_replace_usd(t_token **tokens, t_env *envList)
{
	int	i;
	char	*tmp;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->is_in_quote == '\'' || tokens[i]->is_in_quote == '"')
		{
			manage_in_quote(tokens[i++], envList);
			continue;
		}
		if (tokens[i]->word[0] == '$')
		{
			if (tokens[i]->word[1] == '?')
			{
				free(tokens[i]->word);
				tokens[i]->word = ft_itoa(g_exit_code);
			}
			else
			{
				tmp = ft_get_env_value(tokens[i]->word+1, envList);
				free(tokens[i]->word);
				tokens[i]->word = tmp;
				printf("->expansion: tokens[i]->word = %s\n", tokens[i]->word);
			}
		}
		i++;
	}
}


