/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 01:17:07 by bat               #+#    #+#             */
/*   Updated: 2023/12/12 14:38:44 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command *ft_create_node_for_command(void)
{
    t_command *new_node_command;
    
    new_node_command = (t_command *)malloc(sizeof(t_command));
    
    if (new_node_command == NULL) {
        fprintf(stderr, "Chaos, memory allocation failed with new_node_command\n");
        exit(EXIT_FAILURE);
    }    
    newNode->name = NULL;
    newNode->args = NULL;
    newNode->redirectFile = NULL;
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->tokenType = NOT;
    newNode->state = NORMAL;
    *node = (void *)new_node_command;
    
    return newNode;
}

t_command *ft_create_node_for_envVar(void)
{
    t_env *new_node_env;
    
    new_node_env = (t_env *)malloc(sizeof(t_env));
    
    if (new_node_env == NULL) {
        fprintf(stderr, "Chaos, memory allocation failed with new node\n");
        exit(EXIT_FAILURE);
    }
    new_node_env->name = NULL;
    new_node_env->value = NULL;
    new_node_env->next = NULL;
    new_node_env->prev = NULL;
    *node = (void *)new_node_envVar;
    
    return newNode;
}

void ft_create_node(void **node, t_node_type type) {
    if (node == NULL) {
        return;
    }
    if (type == ENV_NODE) {
        ft_create_node_for_enVar();
    } else if (type == COMMAND_NODE) {
        ft_create_node_for_command();
    }
}
