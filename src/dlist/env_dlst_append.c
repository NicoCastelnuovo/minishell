/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dlst_append.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:33:39 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/25 12:41:12 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_dlst_append(t_env **env, t_var *new)
{
	if (!(*env)->head)
	{
		(*env)->head = new;
		(*env)->tail = new;
		(*env)->size += 1;
		return ;
	}
	(*env)->tail->next = new;
	new->prev = (*env)->tail;
	(*env)->tail = new;
	(*env)->size += 1;
}
