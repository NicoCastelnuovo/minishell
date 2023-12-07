/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:06:56 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/07 11:02:59 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_child_and_exit(t_data *data, char **env, int e_code)
{
	// close pipes !!!!!!!!????
	// free_cmd_node(node);
	if (data)
		free_data(data);
	if (env)
		free_dptr(env);
	exit(e_code);
}

static int	fork_one_ps(t_data *data)
{
	data->pid = ft_calloc(1, sizeof(int));
	if (!data->pid)
	{
		data->e_code = 1;
		return (error("executor", NULL, errno), 1);
	}
	data->pid[0] = fork();
	if (data->pid[0] == -1)
		return (error("fork", NULL, errno), 1);
	if (data->pid[0] == 0)
		child_single_cmd(data);
	return (0);
}

/*
	In case there is no pipe, the builtins has to be executed directly in the
	parent process, otherwise some of them would not take effect. Basic example
	would be "cd" command, which would change the directory inside the child ps
	and not in the parent.
*/
int	execute_single_cmd(t_data *data) // void or int ?
{
	if (is_builtin(data->tree->content))
		return (run_builtin_same_ps(data));
	else
	{
		if (fork_one_ps(data))
		{
			data->e_code = 1;
			return (1);
		}
	}
	return (0);
}
