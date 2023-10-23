/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 08:50:30 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/23 08:49:38 by ncasteln         ###   ########.fr       */
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
	returns the variable of the original env, this would retrieve the value
	of the current env.
*/
char	*get_env_var_value(char *name, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], name, ft_strlen(name)))
			return (env[i] + ft_strlen(name));
		i++;
	}
	ft_putstr_fd("\n", 1);
	return (NULL);
}

void	print_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], 1);
		i++;
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

static t_var	get_env_var_content(char *env_var)
{
	t_var	*var;
	char	**name_value;

	var = ft_calloc(1, sizeof(t_var));
	if (!var)
		return (NULL);
	name_value = ft_split(env_var, '=');
	if (!name_value)
		return (NULL);
	var->name = name_value[0];
	var->value = name_value[1];
	var->name_len = ft_strlen(var->name);
	var->name_len = ft_strlen(var->value);
}

/*
	Copies the environment. In case the environment is ignored with 'env -i'
	option, an empty environment is still created. In such case, env_cpy
	exist, but the first element (env_cpy[0]) is set to NULL.
*/
char	**copy_env(char **env)
{
	t_list	*env_cpy;
	t_var	*var;
	int		i;

	env_cpy = NULL;
	i = 0;
	while (env[i])
	{
		var = ft_calloc(1, sizeof(t_var));
		if (!var)
			return (NULL); // free_content

		ft_lstnew();
		// env_cpy[i] = ft_calloc(ft_strlen(env[i]) + 1, sizeof(char));
		// if (!env_cpy[i])
		// 	return (free_dptr(env_cpy), NULL);
		// ft_strlcpy(env_cpy[i], env[i], ft_strlen(env[i]) + 1);
		i++;
	}
	return (env_cpy);
}
