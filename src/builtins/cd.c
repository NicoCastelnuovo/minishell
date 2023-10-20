/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:20:48 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/20 11:03:15 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_pwd(char **env)
{
	int		i;
	char	*pwd;

	i = 0;
	while (env[i])
	{
		pwd = ft_strnstr(env[i], "PWD=", ft_strlen("PWD="));
		// check if it's correct
		if (pwd)
		{
			env[i] = "--- NEW VAR VALUE! ---";
			break ;
		}
		i++;
	}

}

/*
	cd changes the current working directory of the current shell env. Only a
	relative or an absolute path are accepted.
*/
int	cd(char *path, char **env)
{
	if (!path)
	{
		ft_printf("go home ???");
		return (0);
	}
	if (chdir(path) == -1)
		return (ENOENT);
	set_pwd(env);
	return (0);
}
