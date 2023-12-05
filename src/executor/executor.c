/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 08:31:08 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/05 10:02:29 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	executor(t_data *data)
{
	data->n_ps = get_n_cmds(data->tree);
	if (!data->tree) // right ??
		return (1);
	if (data->tree->type == IS_CMD)
	{
		if (execute_single_cmd(data))
			return (1);
	}
	else
	{
		if (execute_pipechain(data)) // waht happend if a child in the middle fails?
			return (1);
	}
	parent(data);
	return (0);
}
