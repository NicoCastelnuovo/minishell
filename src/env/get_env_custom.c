/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_custom.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:53:39 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/08 17:46:01 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_custom(char *name, t_env *env)
{
	t_var	*head;

	head = env->head; // maybe no need
	if (env->size)
	{
		while (head)
		{
			if (ft_strncmp(head->name, name, ft_strlen(head->name)) == 0)
				return (head->value);
			head = head->next;
		}
	}
	return (NULL);
}
