/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:30:19 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/20 12:38:41 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	option, an empty environmente is still created. In such case, envp_cpy
	exist, but the first element (envp_cpy[0]) is set to NULL.
*/
char	**copy_envp(char **envp)
{
	char	**envp_cpy;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	envp_cpy = ft_calloc(i + 1, sizeof(char *));
	if (!envp_cpy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		envp_cpy[i] = ft_calloc(ft_strlen(envp[i]) + 1, sizeof(char));
		if (!envp_cpy[i])
			return (free_dptr(envp_cpy), NULL);
		ft_strlcpy(envp_cpy[i], envp[i], ft_strlen(envp[i]) + 1);
		i++;
	}
	return (envp_cpy);
}
