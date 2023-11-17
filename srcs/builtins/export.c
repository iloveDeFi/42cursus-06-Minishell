
#include "minishell.h"

int	check_args(char *name)
{
	if (!ft_check_wrong_char(name))
		return (0);
	if (!ft_only_digit(name))
		return (0);
	return (1);
}

int ft_error_export(char *args)
{
    ft_putstr_fd("export: ", STDERR_FILENO);
    ft_putstr_fd(args, STDERR_FILENO);
    ft_putstr_fd(" : Identifer not valid\n", STDERR_FILENO);
    return (EXIT_FAILURE);
}

int ft_check_wrong_char(char *str)
{
    int i;

    i = 0;
    if (str[i] == '=')
        return (0);
    while (str[i])
    {
        if (ft_is_sep(str[i]) || (str[i] >= 33 && str[i] <= 47)
            || (str[i] == '=' && str[i + 1] == '='))
            return (TRUE);
        i++; 
    }
    return (FALSE);   
}
