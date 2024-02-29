		
	#include "minishell.h"

	// TO DO : ft_handle_error() Ajoutez une gestion appropriée des erreurs,
	// comme la vérification des permissions, la gestion des fichiers inexistants, etc.
	// void ft_handle_error(t_commandList *commandList, t_command *command)
	// {
	// 	// if (ft_handle_error_before_execution(command) != 0) {
    //     //     perror("Error: Failed to handle error before execution in ft_launch_parsing_and_execution\n");
    //     //     ft_destroy_commandList(commandList);
	// 	//	   g_exit_code = ERROR_IN_ERROR_BEFORE_EXEC;
    //     //     return 1;
    //     // }
	// 	return 0;
	// }
	
	// int ft_handle_pipe(t_commandList *commandList, t_command *command)
	// {
	// 	if (ft_launch_pipe(command) != 0) {
    //         perror("Error: Failed to handle pipes in ft_launch_parsing_and_execution\n");
    //         ft_destroy_commandList(commandList);
	// 		g_exit_code = ERROR_IN_PIPE_EXEC;
    //         return 1;
    //     }
	// 	return 0;
	// }

	// int ft_handle_redirection(t_commandList *commandList, t_command *command)
	// {
	// 	if (ft_launch_redirection_execution(command) != 0) {
    //         perror("Error: Failed to handle redirection execution in ft_launch_parsing_and_execution\n");
    //         ft_destroy_commandList(commandList);
	// 		g_exit_code = ERROR_IN_REDIRECTION_EXEC;
    //         return 1;
    //     }
	// 	return 0;
	// }

	// int ft_handle_command(t_commandList *commandList, t_command *command, t_env *envList, char **envp)
	// {
	// 	if (ft_launch_command_execution(command, commandList, envList, envp) != 0) {
    //         perror("Error: Failed to handle command execution in ft_launch_parsing_and_execution\n");
    //         ft_destroy_commandList(commandList);
	// 		g_exit_code = ERROR_IN_COMMAND_EXEC;;
    //         return 1;
    //     }
	// 	return 0;
	// }

