/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 08:50:30 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/26 15:35:00 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Outputs the environment variables which are at least an empty string. The
	uninitalized env var are not output like in the standar env builtin.
*/
void	print_env(t_env *env)
{
	t_var	*head;

	head = env->head;
	if (env->size)
	{
		while (head)
		{
			if (head->name && head->value)
			{
				ft_putstr_fd(head->name, 1);
				ft_putchar_fd('=', 1);
				ft_putendl_fd(head->value, 1);
			}
			head = head->next;
		}
	}
}

/*
	Given c as a divider, returns the length of the substring which is on the
	left of it including the divider. Example. Hello=world!!!, if the divider
	is =, it returns 6.
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

/*
	Returns a new t_var struct, which is the potential content for a new node.
	The = sign is omitted and not stored.
	Example. NEW_VAR=hello
		name -> NEW_VAR | value -> hello
*/
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

/*
	Copies the environment variable of the parent process into a double
	linked list, to be used in the current shell.
*/
t_env	*init_env(char **env)
{
	t_env	*env_cpy;
	t_var	*new_node;
	int		i;

	env_cpy = ft_calloc(1, sizeof(t_env)); // protect
	env_cpy->head = NULL;
	env_cpy->tail = NULL;
	env_cpy->size = 0;
	new_node = NULL;
	while (env[i])
	{
		new_node = env_dlst_new(env[i]);
		if (!new_node)
			return (env_dlst_clear(&env_cpy), NULL); // free()
		env_dlst_append(&env_cpy, new_node);
		i++;
	}
	return (env_cpy);
}
