/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_syntax_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:28:35 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/06 10:54:28 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_node(t_node *node_c)
{
	t_cmd	*cmd;

	cmd = node_c->content;
	if (cmd->tokens)
	{
		// free
	}
	if (cmd->args)
	{
		// free dptr
	}
	if (cmd->redir)
	{
		// free t_list
	}
	cmd->fd_in = -1;
	cmd->fd_out = -1;
}

void	free_tree(t_node *tree)
{
	t_node	*root;
	t_pipe	*pipe;
	t_pipe	*temp;

	root = tree;
	while (tree->type == IS_PIPE)
	{
		pipe = (t_pipe *)tree->content;
		// free(pipe->left)
		// free_cmd_node(pipe->left);
		temp = pipe;
		// free current pipe
		tree = temp->right;
	}
}
