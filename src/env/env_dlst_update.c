/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dlst_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:27:56 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/11 17:00:44 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	The function updates the node only if the argument passed in has an equal
	name, otherwise the variable is not modified.
*/
void	env_dlst_update(t_var *new_node, t_env **env)
{
	t_var	*head;
	int		i;

	i = 0;
	head = (*env)->head;
	while (head)
	{
		if (ft_strcmp(head->name, new_node->name) == 0)
		{
			if (head->value && new_node->value)
			{
				if (ft_strcmp(head->value, new_node->value) != 0)
				{
					new_node->prev = head->prev;
					new_node->next = head->next;
					new_node->prev->next = new_node;
					if (i != (*env)->size - 1)
						new_node->next->prev = new_node;
					free_env_node(head);
					head = new_node;
				}
				else
					free_env_node(new_node);
			}
			return ;
		}
		i++;
		head = head->next;
	}
}
