/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:02:10 by bat               #+#    #+#             */
/*   Updated: 2023/10/18 14:26:28 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

# define TEST 49213

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef enum
{
    FALSE,
    TRUE
}   Bool;

// Built-ins

// Excecution  


// libft


// Linked Lists


// Parsing

typedef struct s_argList
{
    int listLength;
    struct s_argList *head;
    struct s_argList *tail;
} t_argList;
typedef struct s_arg
{
    char *name;
    struct s_argList *next;
    struct s_argList *prev;
}   t_arg;

typedef struct s_commandList
{
    int commandListLength;
    char *name;
    struct s_command *head;
    struct s_command *tail;
}   t_commandList;
typedef struct s_command
{
    char *name;
    char **arguments;
    struct s_command *head;
    struct s_command *tail;// Un tableau de chaînes pour les arguments
}   t_command;

typedef struct envVarList 
{
    int envVarListLength;
    struct envVar *head;
    struct envVar *tail;
}   t_envList;
typedef struct s_envVar
{
    char *name;
    char *value;
    struct s_envVar *next;
    struct s_envVar *prev;
}   t_env;  

typedef struct s_Redir
{
    char *file_name;
    t_type  type;
    struct s_redir *next;
    struct s_redir *prev;

}   t_redir;


// Signals

#endif