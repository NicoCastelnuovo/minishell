/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:05:04 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/09 11:06:21 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	if_contains_path(char *cmd_name)
{
	if (cmd_name[0] == '/')
		return (1);
	if (ft_strncmp(cmd_name, "./", 2) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "../", 3) == 0)
		return (1);
	return (0);
}

static int	is_a_directory(char *cmd_name)
{
	struct stat	f_status;

	if (stat(cmd_name, &f_status) == 0 && S_ISDIR(f_status.st_mode))
		return (1);
	return (0);
}

static int	bin_exist_and_can_execute(char *cmd_name, char **abs_path, char	*path)
{
	char	*tmp;

	*abs_path = ft_strjoin(path, "/");
	if (!*abs_path)
		return (-1);
	tmp = *abs_path;
	*abs_path = ft_strjoin(*abs_path, cmd_name);
	if (!*abs_path)
		return (free(tmp), -1);
	free(tmp);
	if (access(*abs_path, F_OK | X_OK) == 0 && !is_a_directory(*abs_path))
		return (0);
	free(*abs_path);
	return (1);
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

/*
	get_abs_path() returns 3 kinds of value: (1) in case no command was found
	inside $PATH; (0) in case of a command was found; (-1) in case of malloc
	errors.
*/
static int	get_abs_path(char *cmd_name, char **abs_path, char **env)
{
	char	*path_var;
	char	**paths;
	int		i;
	int		ret_value;

	ret_value = 0;
	path_var = get_path_var(env);
	if (!path_var)
		return (1);
	paths = ft_split(path_var, ':');
	if (!paths)
		return (1);
	i = 0;
	while (paths[i])
	{
		ret_value = bin_exist_and_can_execute(cmd_name, abs_path, paths[i]);
		if (ret_value == -1)
			return (free_dptr(paths), -1);
		if (ret_value == 0)
			return (free_dptr(paths), 0);
		i++;
	}
	return (free_dptr(paths), 1);
}

/*
	If the cmd_name contains a path, the function verifies if it is a directory
	(/bin) and in that case return (126). If it contains a path but it's not a
	directory (/bin/ls), it verifies F_OK and X_OK, returning (127) in case of
	error (in this case, execve() is not called.
	If cmd_name doesn't contain a path, it is built using the $PATH variable.
	(-1) is returned in case of error, (0) in case of an abs_path is built
	successfully, (1) in case nothing is found.
*/
int	resolve_args(char **cmd_name, char **env)
{
	char	*abs_path;
	char	*tmp;
	int		ret_value;

	abs_path = NULL;
	if (if_contains_path(*cmd_name))
	{
		if (is_a_directory(*cmd_name))
			return (error(*cmd_name, NULL, 126), 126);
		if (access(*cmd_name, F_OK | X_OK) == 0)
			return (0);
		return (error(*cmd_name, NULL, errno), 127);
	}
	ret_value = get_abs_path(*cmd_name, &abs_path, env);
	if (ret_value == -1)
		return (-1);
	if (ret_value == 1)
		return (1);
	tmp = *cmd_name;
	*cmd_name = abs_path;
	free(tmp);
	return (0);
}
