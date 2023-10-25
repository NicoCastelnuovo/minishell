/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dlst_update_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:27:56 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/25 17:07:34 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_dlst_update_value(char *name_value, char *name, t_env **env)
{
	char	*new_value;
	t_var	*head;

	new_value = ft_substr(name_value, ft_strlen(name), ft_strlen(name_value) - ft_strlen(name));
	head = (*env)->head;
	while (head)
	{
		if (ft_strncmp(head->name, name, head->name_len) == 0)
		{
			free(head->value);
			head->value = new_value;
			return ;
		}
		head = head->next;
	}
}
