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

static void	env_dlst_delcontent(t_var *var)
{
	if (var->name)
		free(var->name);
	if (var->value)
		free(var->value);
	var->name_len = -1;
	var->value_len = -1;
	var->next = NULL;
	var->prev = NULL;
}

void	env_dlst_delnode(t_var *node, t_env **env)
{
	if ((*env)->head == (*env)->tail)
	{
		(*env)->head = NULL;
		(*env)->tail = NULL;
		env_dlst_delcontent(node);
		free(node);
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
	env_dlst_delcontent(node);
	free(node);
	(*env)->size -= 1;
}
