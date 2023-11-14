/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:05:04 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/14 13:42:06 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	bin_exists(char *cmd_name, char	*path)
{
	char	*abs_path;
	char	*tmp;

	abs_path = ft_strjoin(path, "/");
	tmp = abs_path;
	abs_path = ft_strjoin(abs_path, cmd_name);
	free(tmp);
	if (access())
	{

	}
	return (0);
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

//PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin:/Users/ncasteln/goinfre/.brew/bin:/Users/ncasteln/.brew/bin:/Users/ncasteln/Projects/minishell

static char	*get_abs_path(char *cmd_name, char **env)
{
	char	**path_var;
	char	*abs_path;
	int		i;

	path_var = ft_split(get_path_var(env), ':');
	i = 0;
	while (path_var[i])
	{
		if (bin_exists(cmd_name, path_var[i]))
		{
			// return it
		}
		i++;
	}

	exit(1);

	// if (cmd_name[0] == '.')

}

int	resolve_args(char **args, char **env)
{
	char	cmd_name;

	cmd_name = get_abs_path(args[0], env);

	// search in case of /bin/ls OR ls OR ./ls
	execve(NULL, NULL, env);
	error(args[0], CE_CMDNOTFOUND);
	exit(127);
}
