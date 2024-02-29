#include "minishell.h" 

void	ft_split_string_export_argument(const char *arg, \
	char **name, char **value)
{
	char	*equals;

	equals = ft_strchr(arg, '=');
	if (equals != NULL)
	{
		*equals = '\0';
		*name = ft_strdup(arg);
		*value = ft_strdup(equals + 1);
	}
	else
	{
		*name = NULL;
		*value = NULL;
	}
}
