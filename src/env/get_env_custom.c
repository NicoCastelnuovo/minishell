/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_custom.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:53:39 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/23 16:41:48 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_custom(char *name, t_list *env)
{
	t_var	*var;
	t_list	*head;

	head = env;
	if (head)
	{
		while (head)
		{
			var = (t_var *)head->content;
			if (ft_strcmp(var->name, name) == 0)
				return (var->value);
			head = head->next;
		}
	}
	return (NULL);
}
