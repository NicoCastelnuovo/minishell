/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dlst_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:27:56 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/06 12:20:47 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	The function updates the node only if the argument passed in has an equal
	as last char, otherwise the variable is not modified.
*/
void	env_dlst_update(t_var *new_node, t_env **env)
{
	t_var	*head;

	head = (*env)->head;
	while (head)
	{
		if (ft_strncmp(head->name, new_node->name, new_node->name_len) == 0)
		{
			new_node->prev = head->prev;
			new_node->next = head->next;
			new_node->prev->next = new_node;
			new_node->next->prev = new_node;
			free_env_node(head);
			head = new_node;
			return ;
		}
		head = head->next;
	}
}
