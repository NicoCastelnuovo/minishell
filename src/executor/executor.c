/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 08:31:08 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/21 07:13:13 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fork_last(t_data *data, t_node *node, int *prev_pipe, int i, char **env)
{
	data->pid[i] = fork();
	if (data->pid[i] == -1)
		return (error("fork", NULL, errno), 1);
	if (data->pid[i] == 0)
		child(node, env, NULL, prev_pipe);
	else
		close(*prev_pipe);
	return (0);
}

static int	fork_ps(t_data *data, t_node *node, int *prev_pipe, int i, char **env)
{
	int		fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		return (error("pipe", NULL, errno), 1);
	data->pid[i] = fork();
	if (data->pid[i] == -1)
		return (error("fork", NULL, errno), 1);
	if (data->pid[i] == 0)
		child(node, env, fd_pipe, prev_pipe);
	else
	{
		close(fd_pipe[1]);
		close(*prev_pipe);
		*prev_pipe = fd_pipe[0];
		// close fd_pipe ??? check
	}
	return (0);
}

static int	get_n_cmds(t_node *node)
{
	t_pipe	*pipe;
	int		n;

	n = 0;
	while (node->type == IS_PIPE)
	{
		pipe = (t_pipe *)node->content;
		n += 1;
		node = pipe->right;
	}
	n += 1;
	return (n);
}

static int	fork_children(t_data *data, char **env, int *prev_pipe)
{
	t_node	*node;
	t_pipe	*pipe;
	int	i;

	node = data->tree;
	i = 0;
	while (node->type == IS_PIPE)
	{
		pipe = (t_pipe *)node->content;
		if (fork_ps(data, pipe->left, prev_pipe, i, env))
			return (1);
		node = pipe->right;
		i++;
	}
	if (fork_last(data, node, prev_pipe, i, env))
		return (1);
	return (0);
}

int	executor(t_data *data)
{
	int		prev_pipe;
	char	**env;

	if (!data->tree)
		return (1);
	prev_pipe = dup(0);
	if (prev_pipe == -1)
	{
		data->e_code = 1;
		return (error("executor", NULL, errno), 1);
	}
	env = convert_to_dptr(data->env);
	data->n_ps = get_n_cmds(data->tree);
	data->pid = ft_calloc(data->n_ps, sizeof(int));
	if (!data->pid)
	{
		data->e_code = 1;
		return (1);
	}
	if (data->tree->type == IS_CMD && is_builtin(data->tree->content))
		return (run_builtin(data));
	if (fork_children(data, env, &prev_pipe))
	{
		data->e_code = 1;
		return (1);
	}
	free_dptr(env);
	parent(data);
	return (0);
}
