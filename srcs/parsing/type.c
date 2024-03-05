#include "minishell.h"

// DO NOT handle commands without spaces as separator i.e. commande>output.txt
// int ft_token_is_redirection(char *token, t_command *currentCommand, int *tokenIndex) 
// {
//     printf("enter in ft_token_is_redirection\n");
// 	char *nextToken;

//     if (ft_strcmp(token, "<") == 0 || ft_strcmp(token, "<<") == 0 || ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0) 
// 	{
//         if (currentCommand != NULL) {
// 			currentCommand->redirection_info.type = ft_parse_all_redirection(token);
//             // Goal next token gonna be the filename currentCommand;
//             nextToken = ft_strtok(NULL, " ");
//             if (nextToken != NULL) {
//                 currentCommand->redirection_info.filename = ft_strdup(nextToken);
//                 currentCommand->redirection_info.delimiter = ft_strdup(nextToken);
//                 (*tokenIndex)++;
// 				free(nextToken);
//             } else {
//     			fprintf(stderr, "Error: Filename is missing after redirection in ft_token_is_redirection.\n");
//                 g_exit_code = 426;
//             }
//         }
//         return 1;
//     }
//     return 0;
// }
