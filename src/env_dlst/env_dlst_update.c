/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dlst_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:27:56 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/26 13:16:05 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	The function updates the node only if the argument passed in has an equal
	as last char, otherwise the variable is not modified.
*/
void	env_dlst_update(char *arg, t_env **env)
{
	t_var	*head;
	t_var	*new_content;
	t_var	*new_node;

	new_content = prepare_env_content(arg);
	if (new_content->name[new_content->name_len - 1] != '=')
	{
		env_dlst_delcontent(new_content);
		return ;
	}
	head = (*env)->head;
	while (head)
	{
		if (ft_strncmp(head->name, new_content->name, new_content->name_len) == 0)
		{
			ft_printf("OLD name & value [%s][%d]  [%s][%d]\n", head->name,  head->name_len, head->value, head->value_len);
			ft_printf("NEW name & value [%s][%d]  [%s][%d]\n", new_content->name,  new_content->name_len,new_content->value, new_content->value_len);
			new_node = env_dlst_new(new_content);
			new_node->prev = head->prev;
			new_node->next = head->next;
			env_dlst_delcontent(head);
			head = new_node;
			return ;
		}
		head = head->next;
	}
}
