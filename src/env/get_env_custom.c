/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_custom.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:53:39 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/13 10:26:09 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_custom(char *name, t_list *env)
{
	t_var	*var;

	if (env)
	{
		while (env)
		{
			var = (t_var *)env->content;
			if (ft_strcmp(var->name, name) == 0)
				return (var->value);
			env = env->next;
		}
	}
	return (NULL);
}
