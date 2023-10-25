/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 08:50:30 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/25 17:14:24 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *env)
{
	t_var	*head;

	head = env->head;
	if (env->size)
	{
		while (head)
		{
			if (head->name)
				ft_putstr_fd(head->name, 1);
			if (head->value)
				ft_putendl_fd(head->value, 1);
			head = head->next;
		}
	}
}

/*
	Given c as a divider, returns the length of the substring which is on the
	left of it. Example. Hello=world!!!, if the divider is =, it returns 5.
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
	return (i);
}

t_var	*prepare_env_content(char *env_var)
{
	t_var	*var;
	char	*key;
	char	*value;

	var = ft_calloc(1, sizeof(t_var));
	if (!var)
		return (NULL);
	var->name_len = get_substr_len(env_var, '=');
	var->name = ft_calloc(var->name_len + 1, sizeof(char)); //protect
	ft_strlcpy(var->name, env_var, var->name_len + 2);
	var->value = ft_substr(env_var, var->name_len + 1, ft_strlen(env_var) - var->name_len);
	var->value_len = ft_strlen(var->value);
	return (var);
}

t_env	*init_env(char **env)
{
	t_env	*env_cpy;
	t_var	*content;
	t_var	*new_node;
	int		i;

	env_cpy = ft_calloc(1, sizeof(t_env)); // protect
	env_cpy->head = NULL;
	env_cpy->tail = NULL;
	env_cpy->size = 0;
	content = NULL;
	new_node = NULL;
	while (env[i])
	{
		content = prepare_env_content(env[i]);
		if (!content)
			return (env_dlst_clear(&env_cpy), NULL); // free()
		new_node = env_dlst_new(content);
		if (!new_node)
		{
			free(content);
			return (env_dlst_clear(&env_cpy), NULL); // free()
		}
		env_dlst_append(&env_cpy, new_node);
		if (content)
			free(content);
		i++;
	}
	return (env_cpy);
}
