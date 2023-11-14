/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 08:31:08 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/14 08:56:08 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_data *data)
{
	t_node	*node;
	t_pipe	*pipe;
	t_cmd	*cmd;

	node = data->tree;
	while (node->type == IS_PIPE)
	{
		pipe = (t_pipe *)node->content;
		cmd = (t_cmd *)pipe->left->content;
		// need
		node = pipe->right;
	}
	cmd = (t_cmd *)node->content;
}
