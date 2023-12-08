/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:05:04 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/08 13:42:53 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*bin_exist_and_can_execute(char *cmd_name, char	*path)
{
	char	*abs_path;
	char	*tmp;

	abs_path = ft_strjoin(path, "/");
	tmp = abs_path;
	abs_path = ft_strjoin(abs_path, cmd_name);
	free(tmp);
	if (access(abs_path, F_OK | X_OK) == 0)
		return (abs_path);
	free(abs_path);
	return (NULL);
}

static char	*get_path_var(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*get_abs_path(char *cmd_name, char **env)
{
	char	*path_var;
	char	**paths;
	char	*abs_path;
	int		i;

	path_var = get_path_var(env);
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		abs_path = bin_exist_and_can_execute(cmd_name, paths[i]);
		if (abs_path)
			return (free_dptr(paths), abs_path);
		i++;
	}
	return (free_dptr(paths), NULL);
}

/*
	resolve_args take the args of the cmd node and build the absolute path
	of the command. In case it doesn't find the absolute path, the original
	cmd_name will be the one which will be passed inside execve(), else,
	the original cmd_name is substituted with abs_path.
*/
int	resolve_args(char **cmd_name, char **env)
{
	char	*abs_path;
	char	*tmp;

	// check if already an abs path (/something)
	// -1 is error ???
	abs_path = get_abs_path(*cmd_name, env);
	if (!abs_path)
		return (1);
	tmp = *cmd_name;
	*cmd_name = abs_path;
	free(tmp);
	return (0);
}
