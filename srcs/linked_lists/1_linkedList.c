/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_linkedList.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 01:14:53 by bat               #+#    #+#             */
/*   Updated: 2023/10/30 10:34:48 by julien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_list(char	*var, t_env **env_list);


void	add_to_list(t_env **env_list, t_env *new_node);


t_env	*get_in_list(char *var, t_env **env_list);

