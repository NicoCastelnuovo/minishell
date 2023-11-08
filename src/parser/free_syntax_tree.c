/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_syntax_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:28:35 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/07 16:45:50 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_dptr(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
}

static void	del_block(void *content)
{
	t_tkn_data	*token;

	token = (t_tkn_data *)content;
	if (!token)
		return ;
	if (token->str)
		free(token->str);
	free(token);
}

static void	del_redir(void *content)
{
	t_redir_data	*redir;

	redir = (t_redir_data *)content;
	if (redir)
	{
		if (redir->file_name)
			free(redir->file_name);
		redir->type = -1;
		free(redir);
	}
}

void	free_cmd_node(t_node *node_c)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)node_c->content;
	if (cmd->block)
		ft_lstclear(&cmd->block, del_block);
	if (cmd->args)
		free_dptr(cmd->args);
	if (cmd->redir)
		ft_lstclear(&cmd->redir, del_redir);
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	free(cmd);
	free(node_c);
}

void	free_pipe_node(t_node *node_p)
{
	t_pipe	*pipe;

	pipe = (t_pipe *)node_p->content;
	if (!node_p)
		return ;
	node_p->n = -1;
	node_p->type = -1;
	free(pipe);
	free(node_p);
}

void	free_tree(t_node *tree)
{
	t_node	*root;
	t_pipe	*pipe;
	t_pipe	*temp;

	root = tree;
	if (tree->type == IS_PIPE)
	{
		while (tree->type == IS_PIPE)
		{
			pipe = (t_pipe *)tree->content;
			free_cmd_node(pipe->left); // left
			temp = pipe->right;
			free_pipe_node(tree);
			tree = temp;
		}
		free_cmd_node(tree);
	}
	else
		free_cmd_node(tree);
}
