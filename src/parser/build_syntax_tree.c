/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_syntax_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:32:21 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/03 16:52:35 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node	*init_node_c(int n)
{
	t_node	*node_c;
	t_cmd	*cmd;

	node_c = ft_calloc (1, sizeof(t_node)); // prtct
	node_c->type = IS_CMD;
	node_c->n = n;
	node_c->content = ft_calloc(1, sizeof(t_cmd)); // prtct
	cmd = (t_cmd *)node_c->content;
	cmd->tkn_sublist = NULL;
	cmd->args = NULL;
	cmd->redir = NULL;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	return (node_c);
}

static t_list	*build_tkn_sublist(t_list *tkn_list, t_node *node_c)
{
	t_tkn_data	*tkn_content;
	t_list		*tkn_sublist;

	tkn_content = (t_tkn_data *)tkn_list->content;
	while (tkn_list && tkn_content->type != '|')
	{
		tkn_content = (t_tkn_data *)tkn_list->content;
		tkn_sublist = ft_lstnew(tkn_content); // protect
		ft_lstadd_back(&((t_cmd *)node_c->content)->tkn_sublist, tkn_sublist);
		if (parse_tkn(&tkn_list, node_c->content))
		{
			// if (((t_cmd *)node_c->content)->err_code) // set t_data
			// free stuff
			return (NULL);
		}
		ft_printf("\n");
		if (tkn_list->next)
			tkn_list = tkn_list->next;
		else
			break ;
	}
	return (tkn_list);
}

static t_node	*init_node_p(int n)
{
	t_node	*node_p;

	node_p = ft_calloc(1, sizeof(t_node)); // protect
	node_p->type = IS_PIPE;
	node_p->n = n + 1;
	node_p->content = ft_calloc(1, sizeof(t_pipe)); // prtct
	((t_pipe *)node_p->content)->left = NULL;
	((t_pipe *)node_p->content)->right = NULL;
	return (node_p);
}

/*
	@param n - just a number to identify which node of the tree it is
	and better visualize it when printed.
*/
t_node	*build_syntax_tree(t_list *tkn_list, int n)
{
	t_node		*node_c;
	t_tkn_data	*tkn_content;
	t_list		*tkn_sublist;
	t_node		*node_p;

	node_c = NULL;
	node_c = init_node_c(n);
	tkn_list = build_tkn_sublist(tkn_list, node_c);
	if (!tkn_list)
	{
		// free stuff
		return (NULL);
	}
	ft_printf("------------------------\n");
	node_p = NULL;
	if (tkn_list->next)
	{
		node_p = init_node_p(n);
		((t_pipe *)node_p->content)->left = node_c;
		((t_pipe *)node_p->content)->right = build_syntax_tree(tkn_list, n + 2);
		if (!((t_pipe *)node_p->content)->right)
		{
			// free current t_node
			return (NULL);
		}
	}
	if (node_p)
		return (node_p);
	return (node_c);
}
