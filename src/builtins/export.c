/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:09:15 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/26 10:19:41 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_var_already_set(char *name, t_env **env)
{
	t_var	*head;

	head = (*env)->head;
	while (head)
	{
		if (ft_strncmp(head->name, name, head->name_len) == 0)
			return (1);
		head = head->next;
	}
	return (0);
}
/*
	NOTES:
	-	export should work with more than one variable (pd)
	-	unspecified result if no argument
	-	what should do a part of setting a varible? It is exported to a subprocess
		but what how can I prove it? Should we handle the VAR=value syntax ??
*/
void	export(char *name_value, t_env **env)
{
	char	*name;
	char	*value;
	int		name_len;
	t_var	*new_content;
	t_var	*new_node;

	name_len = get_substr_len(name_value, '=');
	if (ft_strlen(name_value) == name_len)
		return ;
	name = ft_substr(name_value, 0, name_len + 1); // + 1 take the =
	if (env_var_already_set(name, env))
	{
		env_dlst_update_value(name_value, name, env);
		free(name);
		return ;
	}
	else
	{
		free(name);
		new_content = prepare_env_content(name_value); // protect
		new_node = env_dlst_new(new_content); // protect
		free(new_content);
		env_dlst_append(env, new_node);
	}
}
