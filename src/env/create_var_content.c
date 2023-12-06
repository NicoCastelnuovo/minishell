/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_var_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:15:40 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/06 11:38:10 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Given c as a divider, returns the length of the substring which is on the
	left. Example. Hello=world!!!, if the divider is =, it returns 5.
*/
int	get_substr_len(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i); // changed
}

static char	*get_env_var_value(char *env_var, t_var *var)
{
	char	*var_value;
	int		shlvl;

	// modify this horrible thing
	var_value = ft_substr(env_var, ft_strlen(var->name) + 1, ft_strlen(env_var) - ft_strlen(var->name));
	if (ft_strcmp(var->name, "SHLVL") == 0)
	{
		shlvl = ft_atoi(var_value) + 1;
		free(var_value);
		var_value = ft_itoa(shlvl);
		if (!var_value)
			return (NULL);
	}
	if (ft_strcmp(var->name, "OLDPWD") == 0)
	{
		free(var_value);
		var_value = NULL;
	}
	return (var_value);
}

t_var	*create_var_content(char *env_var)
{
	t_var	*var;

	var = ft_calloc(1, sizeof(t_var));
	if (!var)
		return (NULL);
	var->name_len = get_substr_len(env_var, '=');
	var->name = ft_calloc(var->name_len + 1, sizeof(char));
	if (!var->name)
		return (NULL); // free() ???
	ft_strlcpy(var->name, env_var, var->name_len + 1);
	var->value = get_env_var_value(env_var, var);
	var->value_len = -1;
	if (var->value)
		var->value_len = ft_strlen(var->value);
	return (var);
}
