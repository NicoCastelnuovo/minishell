/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:06:20 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/07 10:34:20 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_tkn(t_tkn_data *curr_tkn, t_tkn_data  *next_tkn)
{
	t_tkn_type	type;

	if (next_tkn)
	{
		ft_printf("PARSE [%s] and [%s]\n", curr_tkn->str, next_tkn->str);
		if (is_redir(curr_tkn->type) && is_redir_syntax_err(curr_tkn, next_tkn))
		{

		}
	}
	else
	{
		ft_printf("PARSE [%s] with (end or pipe)\n", curr_tkn->str);

	}
	return (0);
}

static void	parse_node(t_cmd *cmd)
{
	t_tkn_data	*curr_tkn;
	t_tkn_data	*next_tkn;

	while (cmd->block)
	{
		curr_tkn = NULL;
		next_tkn = NULL;
		curr_tkn = cmd->block->content;
		if (cmd->block->next)
			next_tkn = cmd->block->next->content;
		parse_tkn(curr_tkn, next_tkn);
		cmd->block = cmd->block->next;
	}
}

void	parse_tree(t_node *tree)
{
	t_pipe	*pipe;

	while (tree->type == IS_PIPE)
	{
		pipe = (t_pipe *)tree->content;
		parse_node(pipe->left->content);
		ft_printf("------------------------\n");
		tree = pipe->right;
	}
	parse_node(tree->content);
}

void	parse(t_node *tree)
{
	t_pipe	*pipe;
	t_list	*tkn_sublist;
	t_cmd	*cmd;

	if (tree->type == IS_PIPE)
		parse_tree(tree);
	// else
	// 	parse_node(tree);

	ft_printf("\n");
}
