/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dlst_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:34:43 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/26 15:43:59 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*env_dlst_new(char *env_var)
{
	t_var	*var;
	char	*key;
	char	*value;

	var = ft_calloc(1, sizeof(t_var));
	if (!var)
		return (NULL);
	var->name_len = get_substr_len(env_var, '=');
	var->name = ft_calloc(var->name_len + 1, sizeof(char)); //protect
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
