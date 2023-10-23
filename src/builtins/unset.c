/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:37:54 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/23 08:33:17 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	The environment variable specified by <name> is unset for the current
	environment. If the argument is a variable which doesn't exist, nothing
	happens.
*/
void	unset_env_var(char *name, char **env)
{
	char	*is_found;
	char	*tmp;
	int		i;

	i = 0;
	while (env[i])
	{
		is_found = ft_strnstr(env[i], name, ft_strlen(name));
		if (is_found)
		{
			// free the corresponding pointer
			// set it to null
			// make a copy of the dptr, and only of the elements which have something
			// destroy the old dptr
			// set the new one as the new updated environment
			break ;
		}
		i++;
	}
}
