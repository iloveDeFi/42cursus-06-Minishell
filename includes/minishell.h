/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:02:10 by bat               #+#    #+#             */
/*   Updated: 2023/10/16 16:21:28 by bat              ###   ########.fr       */
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

typedef struct EnvList 
{
    struct EnvVar *head;
}   t_EnvList;

// libft


// Linked Lists
typedef struct s_Env
{
    char *name;
    char *value;
    struct s_EnvVar *next;
    struct s_EnvVar *prev;
}   t_env;  

// Parsing

// Signals

#endif