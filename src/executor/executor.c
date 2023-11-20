/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 08:31:08 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/20 12:36:11 by ncasteln         ###   ########.fr       */
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
		n++;
		node = pipe->right;
	}
	n++;
	return (n);
}

int	executor(t_data *data)
{
	t_node	*node;
	t_pipe	*pipe;
	int		i;
	int		prev_pipe;
	char	**env;

	if (data->e_code)
		return (1);
	prev_pipe = dup(0);
	env = convert_to_dptr(data->env);
	data->n_ps = get_n_cmds(data->tree);
	data->pid = ft_calloc(data->n_ps, sizeof(int)); // protect
	node = data->tree;
	if (node->type == IS_CMD && is_builtin(node->content))
		return (run_builtin(data));
	i = 0;
	while (node->type == IS_PIPE)
	{
		pipe = (t_pipe *)node->content;
		if (fork_ps(data, pipe->left, &prev_pipe, i, env))
			return (1);
		node = pipe->right;
		i++;
	}
	if (fork_last(data, node, &prev_pipe, i, env))
		return (1);
	free_dptr(env);
	parent(data); // prev pipe should be already closed
	return (0);
}
