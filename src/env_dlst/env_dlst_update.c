/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dlst_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:27:56 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/26 15:11:30 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	The function updates the node only if the argument passed in has an equal
	as last char, otherwise the variable is not modified.
*/
void	env_dlst_update(t_var *new_content, t_env **env)
{
	t_var	*head;
	t_var	*new_node;

	head = (*env)->head;
	while (head)
	{
		if (ft_strncmp(head->name, new_content->name, new_content->name_len) == 0)
		{
			// ft_printf("OLD name & value [%s][%d]  [%s][%d]\n", head->name,  head->name_len, head->value, head->value_len);
			// ft_printf("NEW name & value [%s][%d]  [%s][%d]\n", new_content->name,  new_content->name_len,new_content->value, new_content->value_len);
			new_node = env_dlst_new(new_content);
			free(new_content);
			new_node->prev = head->prev;
			if (new_node->prev)
			{
				// ft_printf("\nBefore [%s]\n", head->prev->name);
				new_node->prev->next = new_node;
			}
			// ft_printf("Current [%s]\n", head->name);
			new_node->next = head->next;
			if (new_node->next)
			{
				// ft_printf("After [%s]\n\n", head->next->name);
				new_node->next->prev = new_node;
			}
			env_dlst_delcontent(head);
			head = new_node;
			return ;
		}
		head = head->next;
	}
}
