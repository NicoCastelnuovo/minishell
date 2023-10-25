/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dlst_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:34:43 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/25 10:54:29 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*env_dlst_new(t_var *content)
{
	t_var	*new_node;

	new_node = malloc(sizeof(t_var));
	if (!new_node)
		return (NULL);
	new_node->name = content->name;
	new_node->name_len = content->name_len;
	new_node->value = content->value;
	new_node->value_len = content->value_len;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}
