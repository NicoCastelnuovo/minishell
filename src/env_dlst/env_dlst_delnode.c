/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_delnode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:35:25 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/23 12:51:35 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_var *node)
{
	if (node->name)
		free(node->name);
	if (node->value)
		free(node->value);
	node->name_len = -1;
	node->value_len = -1;
	node->next = NULL;
	node->prev = NULL;
	free(node);
}

/*
	The function removes the node from the dlst and reset the next and prev
	nodes, so that the dlst is not broken.
*/
void	env_dlst_delnode(t_var *node, t_env **env)
{
	if ((*env)->head == (*env)->tail)
	{
		(*env)->head = NULL;
		(*env)->tail = NULL;
		free_node(node);
		(*env)->size -= 1;
		return ;
	}
	else if ((*env)->head == node)
	{
		(*env)->head = node->next;
		(*env)->head->prev = NULL;
	}
	else if ((*env)->tail == node)
	{
		(*env)->tail = node->prev;
		(*env)->tail->next = NULL;
	}
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	free_node(node);
	(*env)->size -= 1;
}
