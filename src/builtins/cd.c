/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:20:48 by ncasteln          #+#    #+#             */
/*   Updated: 2023/10/20 16:13:58 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Generic function to set an already existing environment variable, passing
	its name, the desired value and the env itself. The function assumes
	that the variable exist and doesn't handle the creation of a new one.
*/
static void	set_env_var(char *name, char *value, char **env)
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
	// if (!is_found)
	//	hast to be created
}

/*
	cd changes the current working directory of the current shell env. Only a
	relative or an absolute path are accepted.
*/
int	cd(char *path, char **env)
{
	char	*old_dir;
	char	*new_dir;

	if (chdir(path) == -1)
		return (ENOENT);
	new_dir = ft_strdup(get_wd(NULL));
	set_env_var("PWD=", new_dir, env);
	return (0);
}
