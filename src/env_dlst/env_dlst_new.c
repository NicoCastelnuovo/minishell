/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dlst_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:34:43 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/27 15:09:24 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Given c as a divider, returns the length of the substring which is on the
	left of it including the divider. Example. Hello=world!!!, if the divider
	is =, it returns 6.
*/
static int	get_substr_len(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

/*
	Returns a new t_var struct, which is the potential content for a new node.
	The = sign is omitted and not stored.
	Example. NEW_VAR=hello
		name -> NEW_VAR | value -> hello
*/
t_var	*env_dlst_new(char *env_var)
{
	t_var	*var;

	var = ft_calloc(1, sizeof(t_var));
	if (!var)
		return (NULL);
	var->name_len = get_substr_len(env_var, '=');
	var->name = ft_calloc(var->name_len + 1, sizeof(char)); //protect
	if (!var->name)
		return (NULL);
	ft_strlcpy(var->name, env_var, var->name_len + 1);
	if (ft_strchr(env_var, '='))
	{
		var->value = ft_substr(env_var, var->name_len + 1, ft_strlen(env_var) - var->name_len);
		var->value_len = ft_strlen(var->value);
	}
	else
	{
		var->value = NULL;
		var->value_len = -1;
	}
	var->next = NULL;
	var->prev = NULL;
	return (var);
}
