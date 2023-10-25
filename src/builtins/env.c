/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 08:50:30 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/25 13:15:43 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Generic function to update an already existing environment variable, passing
	its name, the desired value and the env itself. The function assumes
	that the variable exist and doesn't handle the creation of a new one.
*/
void	update_env_var(char *name, char *value, char **env)
{
	char	*is_found;
	char	*tmp;
	char	*name_value;
	int		i;

	i = 0;
	while (env[i])
	{
		is_found = ft_strnstr(env[i], name, ft_strlen(name));
		if (is_found)
		{
			name_value = ft_strjoin(name, value);
			tmp = env[i];
			env[i] = ft_strdup(name_value);
			free(tmp);
			free(name_value);
			break ;
		}
		i++;
	}
}

/*
	The function replicate getenv() function from stdlib.h. Since getenv()
	returns the variable of the original env, this would retrieve the values
	of the current env.
*/
t_var	*search_var(char *name, t_list *env)
{
	t_var	*var;

	while (env)
	{
		var = (t_var *)env->content;
		if (ft_strncmp(name, var->name, var->name_len) == 0)
			return (var);
		env = env->next;
	}
	return (NULL);
}

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

static void	free_dptr(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
}

static char	*get_var_value(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (ft_strdup(s + i + 1));
		i++;
	}
	return (NULL);
}

static char	*get_var_key(char *s)
{
	int		i;
	char	*key;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
		{
			i++;
			break ;
		}
		i++;
	}
	key = ft_calloc(i + 1, sizeof(char)); // protect
	ft_strlcpy(key, s, i + 1);
	return (key);
}

static t_var	*prepare_node_content(char *env_var)
{
	t_var	*var;
	char	*key;
	char	*value;

	var = ft_calloc(1, sizeof(t_var));
	// protect
	var->name = get_var_key(env_var);
	var->value = get_var_value(env_var);
	var->name_len = ft_strlen(var->name);
	var->value_len = ft_strlen(var->value);
	return (var);
}

t_env	*init_env(char **env)
{
	t_var	*content;
	t_var	*new_node;
	t_env	*env_cpy;
	int		i;

	env_cpy = ft_calloc(1, sizeof(t_env)); // protect
	env_cpy->head = NULL;
	env_cpy->tail = NULL;
	env_cpy->size = 0;
	while (env[i])
	{
		content = prepare_node_content(env[i]);
		new_node = env_dlst_new(content);
		if (!new_node)
			return (NULL); // free()
		env_dlst_append(&env_cpy, new_node);
		i++;
	}
	return (env_cpy);
}
