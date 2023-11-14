/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:05:04 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/14 14:35:35 by ncasteln         ###   ########.fr       */
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
}

static char	*get_abs_path(char *cmd_name, char **env)
{
	char	**path_var;
	char	*abs_path;
	int		i;

	path_var = ft_split(get_path_var(env), ':');
	i = 0;
	while (path_var[i])
	{
		abs_path = bin_exist_and_can_execute(cmd_name, path_var[i]);
		if (abs_path)
			return (abs_path);
		i++;
	}
	return (NULL);
}

void	resolve_args(char **cmd_name, char **env)
{
	char	*abs_path;
	char	**tmp;

	abs_path = get_abs_path(*cmd_name, env);
	if (abs_path)
	{
		tmp = *cmd_name;
		*cmd_name = abs_path;
		free(tmp);
	}
}
