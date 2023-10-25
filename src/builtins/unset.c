/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:37:54 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/25 14:48:38 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	The environment variable specified by <name> is unset for the current
	environment. If the argument is a variable which doesn't exist, nothing
	happens.
*/
void	unset_env_var(char *name, t_env **env)
{
	t_var	*head;

	if (!name || (*env)->size == 0)
		return ;
	head = (*env)->head;
	while (head)
	{
		if (ft_strncmp(name, head->name, head->name_len) == 0)
			env_dlst_delnode(head, env);
		head = head->next;
	}
}
