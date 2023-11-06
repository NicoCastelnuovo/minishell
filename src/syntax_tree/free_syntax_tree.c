/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_syntax_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:28:35 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/06 16:57:14 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_dptr(char **p)
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
	t_redir	*redir;

	redir = (t_redir *)content;
	if (redir)
	{
		if (redir->file_name)
			free(redir->file_name);
		redir->type = -1;
		free(redir);
	}
}

void	free_node_c(t_node *node_c)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)node_c->content;
	print_tokens(((t_cmd *)node_c->content)->block); // remove
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
	ft_printf(" W T F! \n");
}

void	free_node_p(t_node *node_p)
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
			free_node_c(pipe->left); // left
			temp = pipe->right;
			free_node_p(tree);
			tree = temp;
		}
		free_node_c(tree);
	}
	// else
	// 	free_node_c(tree->content);
}
