/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dlst_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:47:06 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/25 14:15:10 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_dlst_clear(t_env **env)
{
	t_var	*next;

	next = NULL;
	if (!*env)
		return ;
	while ((*env)->head)
	{
		next = (*env)->head->next;
		env_dlst_delcontent((*env)->head);
		(*env)->head = next;
	}
	free(*env);
}
