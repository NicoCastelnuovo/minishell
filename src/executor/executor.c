/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 08:31:08 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/14 13:20:07 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

/*
	The first child will
*/
static int	fork_ps(t_data *data, t_cmd *cmd, int *prev_pipe, int i)
{
	char	**env;
	int		fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		return (1);
	env = convert_to_dptr(data->env);
	data->pid[i] = fork();
	if (data->pid[i] == -1)
		return (1);
	if (data->pid[i] == 0)
	{
		if (i == 0)
			first_child(cmd, env, fd_pipe, NULL);
		else if (i == data->n_ps - 1)
			last_child(cmd, env, fd_pipe, prev_pipe);
		else
			mid_child(cmd, env, fd_pipe, prev_pipe);
	}
	else
	{
		close(fd_pipe[1]);
		close(*prev_pipe);
		*prev_pipe = fd_pipe[0];
		// close fd_pipe ???
	}
	return (0);
}

static int	get_n_cmds(t_node *node)
{
	t_pipe	*pipe;
	t_cmd	*cmd;
	int		n;

	n = 0;
	while (node->type == IS_PIPE)
	{
		pipe = (t_pipe *)node->content;
		cmd = (t_cmd *)pipe->left->content;
		n++;
		node = pipe->right;
	}
	cmd = (t_cmd *)node->content;
	n++;
	return (n);
}

int	executor(t_data *data)
{
	t_node	*node;
	t_pipe	*pipe;
	t_cmd	*cmd;
	int		i;
	int		prev_pipe;

	prev_pipe = dup(0);
	// if (node->type == IS_CMD)
		// builtins
	data->n_ps = get_n_cmds(data->tree);
	data->pid = ft_calloc(data->n_ps, sizeof(int)); // protect
	node = data->tree;
	i = 0;
	while (node->type == IS_PIPE)
	{
		pipe = (t_pipe *)node->content;
		cmd = (t_cmd *)pipe->left->content;
		if (fork_ps(data, cmd, &prev_pipe, i))
			return (1);
		node = pipe->right;
		i++;
	}
	cmd = (t_cmd *)node->content;
	if (fork_ps(data, cmd, &prev_pipe, i))
		return (1);
	close(prev_pipe);
	parent(data);
	return (0);
}
