/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 08:50:30 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/20 16:01:25 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	The function replicate getenv() function from stdlib.h. Since getenv()
	returns the variable of the original env, this would retrieve the value
	of the current env.
*/
char	*get_env_var(char *name, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], name, ft_strlen(name)))
			return (env[i]);
		i++;
	}
	return ("\n");
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

/*
	Copies the environment. In case the environment is ignored with 'env -i'
	option, an empty environment is still created. In such case, env_cpy
	exist, but the first element (env_cpy[0]) is set to NULL.
*/
char	**copy_env(char **env)
{
	char	**env_cpy;
	int		i;

	i = 0;
	while (env[i])
		i++;
	env_cpy = ft_calloc(i + 1, sizeof(char *));
	if (!env_cpy)
		return (NULL);
	i = 0;
	while (env[i])
	{
		env_cpy[i] = ft_calloc(ft_strlen(env[i]) + 1, sizeof(char));
		if (!env_cpy[i])
			return (free_dptr(env_cpy), NULL);
		ft_strlcpy(env_cpy[i], env[i], ft_strlen(env[i]) + 1);
		i++;
	}
	return (env_cpy);
}
